/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_comm_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:11:38 by user              #+#    #+#             */
/*   Updated: 2024/09/23 11:52:23 by descamil         ###   ########.fr       */
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
		if (cmd->args && cmd->args[0] && ft_nothing(cmd->args[0], 0) == 0)
			printf("[%s]: command not found\n", cmd->args[0]);
		if (cmd->type)
		{
			if (cmd->names->fd_infile > 0)
				close(cmd->names->fd_infile);
			if (cmd->names->fd_outfile > 1)
				close(cmd->names->fd_outfile);
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
	ft_close_and_update_fds(mini, 'H');
	if (cmd->built == 1)
	{
		ft_exec_built(cmd);
		ft_putstr_fd("BUILT\n", 2);
		close(mini->fd_pipe[1]);
		close(mini->fd_history);
		exit(0);
	}
	else
	{
		execve(cmd->cmd, cmd->args, mini->env->env);
		perror("Execve Error");
	}
}

void	ft_comm(t_cmd *cmd, t_mini *mini)
{
	ft_comm_part1(cmd, mini);
	if (cmd->names->fd_infile != -1 && cmd->names->fd_outfile != -1
		&& cmd->files->error != -3 && mini->error != -4)
	{
		mini->proc[mini->index] = fork();
		if (mini->proc[mini->index] == -1)
			perror("Failed in Fork()");
		if (mini->proc[mini->index] == 0)
			ft_comm_part2(cmd, mini);
	}
	ft_close_and_update_fds(mini, 'P');
	if (cmd->names->join)
	{
		unlink(cmd->names->join);
		free(cmd->names->join);
	}
}
