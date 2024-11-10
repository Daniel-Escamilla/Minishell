/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_comm_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:11:38 by user              #+#    #+#             */
/*   Updated: 2024/11/10 19:39:31 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

static void	ft_comm_part1(t_cmd *cmd, t_mini *mini)
{
	if (mini->num_comm != 0)
	{
		if (pipe(mini->fd_pipe) == -1)
			ft_perror_exit("Pipe Error", 1);
	}
	ft_open_fd(cmd, mini);
	if (cmd->cmd == NULL)
		if (cmd->args && cmd->args[0] && ft_nothing(cmd->args[0], 0) == 0
			&& ft_is_dir(cmd->args[0]) == 0)
			g_exit_status = 127;
	if (cmd->names->fd_infile < 0 || cmd->names->fd_outfile < 1)
		mini->error = -4;
	else
		mini->error = 0;
}

static void	ft_comm_part2(t_cmd *cmd, t_mini *mini, int status)
{
	dup2(cmd->names->fd_infile, STDIN_FILENO);
	dup2(cmd->names->fd_outfile, STDOUT_FILENO);
	ft_close_and_update_fds(mini, cmd, 'H');
	close(mini->fd_history);
	if (cmd->built == 1)
	{
		status = (int)ft_exec_built(mini, cmd);
		if (cmd->names->fd_infile > 0
			&& cmd->names->fd_infile != mini->fd_pipe[0])
			close (cmd->names->fd_infile);
		if (cmd->names->fd_outfile > 1
			&& cmd->names->fd_outfile != mini->fd_pipe[1])
			close (cmd->names->fd_outfile);
		if (mini->fd_tmp > 0 && mini->fd_tmp != cmd->names->fd_infile)
			close(mini->fd_tmp);
		exit(status);
	}
	else
	{
		execve(cmd->cmd, cmd->args, mini->env->env);
		if (ft_strnstr(cmd->args[0], "./", 2))
			ft_printf_exit(cmd->args[0], ": Is a directory\n", 126);
		exit(139);
	}
}

static void	ft_child(t_mini *mini, t_cmd *cmd)
{
	int	dup_fd;
	int	fd;

	if (cmd->cmd == NULL)
	{
		fd = 2;
		while (++fd < 1024)
		{
			dup_fd = dup(fd);
			if (dup_fd != -1)
			{
				close(fd);
				close(dup_fd);
			}
		}
		cmd->names->fd_infile = -1;
		cmd->names->fd_outfile = -1;
		mini->fd_tmp = -1;
		if (cmd->args && cmd->args[0]
			&& ft_nothing(cmd->args[0], 0) == 0)
			ft_printf_exit(cmd->args[0], ": command not found\n", 127);
		exit(1);
	}
	ft_comm_part2(cmd, mini, 0);
}

void	ft_comm(t_cmd *cmd, t_mini *mini)
{
	ft_comm_part1(cmd, mini);
	if (mini->single == 1 && cmd->built == 1)
		g_exit_status = (int)ft_exec_built(mini, cmd);
	else if (cmd->names->fd_infile != -1 && cmd->names->fd_outfile != -1
		&& mini->error != -4)
	{
		mini->proc[mini->index] = fork();
		if (mini->proc[mini->index] == -1)
			ft_perror_exit("Error in Fork", 1);
		if (mini->proc[mini->index] == 0)
			ft_child(mini, cmd);
	}
	ft_close_and_update_fds(mini, cmd, 'P');
}
