/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_files.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:03:10 by descamil          #+#    #+#             */
/*   Updated: 2024/11/24 16:43:43 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/files.h"

static int	ft_mem_files(t_mini *mini, t_cmd *cmd)
{
	int	num_f;

	if (mini->flags->redirect && mini->flags->redirect->number > 0)
	{
		num_f = ft_num_files(cmd);
		cmd->files->f_order = (char **)ft_calloc(sizeof(char *),
				(size_t)num_f + 1);
		if (cmd->files->f_order == NULL)
			return (-1);
	}
	return (0);
}

static int	ft_pos_files(t_cmd *cmd, int i)
{
	int	files;

	files = 0;
	while (cmd->args[i])
	{
		if (ft_type(cmd->args[i++]) > 0)
		{
			if (cmd->args[i] == NULL)
			{
				printf("mini: syntax error near unexpected token `newline'\n");
				g_exit_status = 2;
				return (-1);
			}
			else
				cmd->files->f_order[files++] = ft_strdup(cmd->args[i]);
		}
	}
	return (0);
}

void	ft_files(t_cmd *cmd, t_mini *mini)
{
	if (mini->flags->redirect && mini->flags->redirect->number > 0)
		cmd->files->order = ft_order(cmd, mini);
	if (cmd->files->order == NULL)
		mini->cmd->files->error = -1;
	if (mini->cmd->files->error == -1)
	{
		mini->error = -2;
		return ;
	}
	if (cmd->args)
	{
		if (ft_mem_files(mini, cmd) == -1)
		{
			mini->cmd->files->error = -1;
			return ;
		}
		if (ft_pos_files(cmd, 0) == -1)
		{
			mini->error = -2;
			mini->cmd->files->error = -1;
		}
	}
}
