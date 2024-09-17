/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_comm_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:11:38 by user              #+#    #+#             */
/*   Updated: 2024/09/17 16:39:42 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_comm_part1(t_cmd *cmd, t_mini *mini)
{
	if (mini->num_comm != 0)
	{
		if (pipe(mini->fd_pipe) == -1)
			perror("Pipe Error");
	}
	ft_open_fd(cmd, mini);
	if (cmd->cmd == NULL && mini->error != -2)
	{
		if (cmd->args[0] && cmd->args[0][0] != '^')
			printf("%s: command not found\n", cmd->args[0]);
		if (cmd->type != NULL)
		{
			if (cmd->names->fd_infile)
				close(cmd->names->fd_infile);
			if (cmd->names->fd_outfile)
				close(cmd->names->fd_outfile);
		}
	}
	if (cmd->cmd == NULL || (cmd->names->fd_infile < 0 || cmd->names->fd_outfile < 1))
		mini->error = -4;
	else
		mini->error = 0;
}

void	ft_comm_part2(t_cmd *cmd, t_mini *mini)
{
	dup2(cmd->names->fd_infile, STDIN_FILENO);
	dup2(cmd->names->fd_outfile, STDOUT_FILENO);
	ft_close_fd(mini, 'H');
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

void	ft_comm_part3(t_cmd *cmd, t_mini *mini)
{
	if (cmd->names->fd_infile != STDIN_FILENO && cmd->names->fd_infile > 0)
	{
		close(cmd->names->fd_infile);
		cmd->names->fd_infile = -1;
	}
	if (cmd->names->fd_outfile != STDOUT_FILENO && cmd->names->fd_outfile > 1
		&& mini->fd_pipe[1] != cmd->names->fd_outfile)
	{
		close(cmd->names->fd_outfile);
		cmd->names->fd_outfile = -1;
	}
	ft_close_fd(mini, 'P');
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
		ft_comm_part3(cmd, mini);
	}
	if (mini->fd_tmp > 1)
		close(mini->fd_tmp);
	mini->fd_tmp = mini->fd_pipe[0];
	if (mini->num_comm == 1)
		close(mini->fd_tmp);
	if (mini->fd_pipe[1] > 2)
		close(mini->fd_pipe[1]);
	if (cmd->names->join)
	{
		unlink(cmd->names->join);
		free(cmd->names->join);
	}
}
