/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_comm_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:11:38 by user              #+#    #+#             */
/*   Updated: 2024/10/13 18:05:15 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

void	ft_comm_part1(t_cmd *cmd, t_mini *mini)
{
	if (mini->num_comm != 0)
	{
		if (pipe(mini->fd_pipe) == -1)
			ft_perror_exit("Pipe Error", 1);
	}
	ft_open_fd(cmd, mini);
	if (cmd->cmd == NULL)
	{
		if (cmd->args && cmd->args[0] && ft_nothing(cmd->args[0], 0) == 0
			&& ft_is_dir(cmd->args[0]) == 0)
			ft_printf_exit(cmd->args[0], ": command not found\n", 127);
		if (cmd->type)
		{
			if (cmd->names->fd_infile > 0)
			{
				close(cmd->names->fd_infile);
				cmd->names->fd_infile = -1;
			}
			if (cmd->names->fd_outfile > 1)
			{
				close(cmd->names->fd_outfile);
				cmd->names->fd_outfile = -1;
			}
		}
	}
	if (cmd->cmd == NULL || (cmd->names->fd_infile < 0
			|| cmd->names->fd_outfile < 1))
		mini->error = -4;
	else
		mini->error = 0;
}

void	ft_comm_part2(t_cmd *cmd, t_mini *mini)
{
	int	status;

	dup2(cmd->names->fd_infile, STDIN_FILENO);
	dup2(cmd->names->fd_outfile, STDOUT_FILENO);
	ft_close_and_update_fds(mini, cmd, 'H');
	if (cmd->built == 1)
	{
		status = ft_exec_built(mini, cmd);
		ft_putstr_fd("BUILT\n", 2);
		if (cmd->names->fd_infile > 0
			&& cmd->names->fd_infile != mini->fd_pipe[0])
			close (cmd->names->fd_infile);
		if (cmd->names->fd_outfile > 1
			&& cmd->names->fd_outfile != mini->fd_pipe[1])
			close (cmd->names->fd_outfile);
		close(mini->fd_history);
		if (mini->fd_tmp > 0)
			close(mini->fd_tmp);
		exit(status);
	}
	else
	{
		execve(cmd->cmd, cmd->args, mini->env->env);
		perror("execve");
		exit(1);
	}
}

void	ft_comm(t_cmd *cmd, t_mini *mini)
{
	ft_comm_part1(cmd, mini);
	if (mini->single == 1 && cmd->built == 1)
		g_exit_status = ft_exec_built(mini, cmd);
	else if (cmd->names->fd_infile != -1 && cmd->names->fd_outfile != -1
		&& cmd->files->error != -3 && mini->error != -4)
	{
		mini->proc[mini->index] = fork();
		if (mini->proc[mini->index] == -1)
			ft_perror_exit("Failed in Fork()", 1);
		if (mini->proc[mini->index] == 0)
			ft_comm_part2(cmd, mini);
	}
	ft_close_and_update_fds(mini, cmd, 'P');
	if (cmd->names->join)
	{
		unlink(cmd->names->join);
		free(cmd->names->join);
	}
}
