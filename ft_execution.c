/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:25:25 by user              #+#    #+#             */
/*   Updated: 2024/08/16 12:11:40 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_setvalues(t_cmd *cmd, t_mini *mini)
{
	cmd->names->fd = 0;
	cmd->names->index = 0;
	mini->num_comm = mini->flags->pipe + 1;
	cmd->names->proc = ft_calloc(sizeof(int), mini->num_comm + 1);
}

int	ft_pick_infile(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->type->infile == 1)
	{
		while (ft_atoi(cmd->files->order[i]) == 1 || i == 0)
		{
			if (access(cmd->files->f_order[i], R_OK) == -1)
				return (-2);
			i++;
		}
		return (open(cmd->type->in, O_RDONLY));
	}
	i = 0;
	if (cmd->type->here_doc == 1)
	{
		while (ft_atoi(cmd->files->order[i]) == 3 || i == 0)
		{
			if (access(cmd->files->f_order[i], R_OK) == -1)
				return (-2);
			i++;
		}
		return (open(cmd->type->in, O_RDONLY));
	}
}

int	ft_pick_outfile(t_cmd *cmd)
{
	
}


int	ft_choose_infile(t_cmd *cmd, t_mini *mini)
{
	int	fd;

	if (cmd->type->infile == 1 || cmd->type->here_doc == 1)
		return (ft_pick_infile(cmd));
	else if (mini->fd_tmp != -1)
		return (mini->fd_tmp);
	return (STDIN_FILENO);
}
int	ft_choose_outfile(t_cmd *cmd, t_mini *mini)
{
	int	fd;

	if (cmd->type->outfile == 1 || cmd->type->append == 1)
		return (ft_pick_outfile(cmd));
	else if (mini->num_comm == 1)
		return (STDOUT_FILENO);
	return (cmd->names->fd_pipe[1]);
}

void	ft_comm(t_cmd *cmd, t_mini *mini)
{
	if (pipe(cmd->names->fd_pipe) == -1)
		ft_error_bonus("Pipe Error", 1);
	cmd->names->proc[cmd->names->index] = fork();
	if (cmd->names->proc[cmd->names->index] == -1)
		ft_error_bonus("Failed in Fork()", 1);
	if (cmd->names->proc[cmd->names->index] == 0)
	{
		close(cmd->names->fd_pipe[0]);
		cmd->names->fd_infile = ft_choose_infile(cmd, mini);
		cmd->names->fd_outfile = ft_choose_outfile(cmd, mini);
		dup2(cmd->names->fd_infile, STDIN_FILENO);
		dup2(cmd->names->fd_outfile, STDOUT_FILENO);
		close(cmd->names->fd_infile);
		close(cmd->names->fd_outfile);
		execve(cmd->cmd, cmd->args, mini->env->env);
	}
	if (mini->fd_tmp != 0)
	{
		close(mini->fd_tmp);
		mini->fd_tmp = cmd->names->fd_pipe[0];
	}
	cmd->names->index++;
	if (mini->num_comm == 1)
		close(cmd->names->fd_pipe[1]);
}

int	ft_wait_bonus(t_cmd *cmd)
{
	int	state;
	int i;

	i = 0;
	while (cmd->names->proc[i] && i + 1 < cmd->names->index)
		waitpid(cmd->names->proc[i++], NULL, 0);
	waitpid(cmd->names->proc[i], &state, 0);
	return (state);
}
