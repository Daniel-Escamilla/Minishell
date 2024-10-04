/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_comm_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:11:38 by user              #+#    #+#             */
/*   Updated: 2024/10/04 12:21:52 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

void	ft_comm_part1(t_cmd *cmd, t_mini *mini)
{
	if (mini->num_comm != 0)
	{
		if (pipe(mini->fd_pipe) == -1)
			perror("Pipe Error");
	}
	ft_open_fd(cmd, mini);
	if (cmd->cmd == NULL)
	{
		if (cmd->args && cmd->args[0] && ft_nothing(cmd->args[0], 0) == 0
			&& ft_is_dir(cmd->args[0]) == 0)
			printf("%s: command not found\n", cmd->args[0]);
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
	dup2(cmd->names->fd_infile, STDIN_FILENO);
	dup2(cmd->names->fd_outfile, STDOUT_FILENO);
	ft_close_and_update_fds(mini, cmd, 'H');
	if (cmd->built == 1)
	{
		ft_exec_built(mini, cmd);
		ft_putstr_fd("BUILT\n", 2);
		// close(mini->fd_pipe[1]);
		close(mini->fd_history);
		close(2);
		close(1);
		close(0);
		exit(0);
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
	if (mini->single == 1 && cmd->built == 1 && ft_strncmp(cmd->cmd, "cd", 2) == 0 && ft_strlen(cmd->cmd) == 2)
		ft_cd(mini, cmd);
	else if (cmd->names->fd_infile != -1 && cmd->names->fd_outfile != -1
		&& cmd->files->error != -3 && mini->error != -4)
	{
		mini->proc[mini->index] = fork();
		if (mini->proc[mini->index] == -1)
			perror("Failed in Fork()");
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
