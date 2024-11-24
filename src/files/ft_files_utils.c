/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_files_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 08:59:47 by descamil          #+#    #+#             */
/*   Updated: 2024/11/24 16:40:49 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/files.h"

void	process_lines(t_cmd **cmd, t_mini *mini, char **lines, int i)
{
	t_cmd	*cmd_cmd;
	t_cmd	*current;

	while (lines && lines[i] != NULL)
	{
		cmd_cmd = ft_add_command(lines[i++], -1);
		if (*cmd == NULL)
			*cmd = cmd_cmd;
		else
		{
			current = *cmd;
			while (current->next != NULL)
				current = current->next;
			current->next = cmd_cmd;
		}
		ft_move_files(cmd_cmd, mini);
		if (mini->cmd->files->error == -1)
			return ;
	}
}

void	ft_move_files(t_cmd *cmd, t_mini *mini)
{
	cmd->files = ft_calloc(sizeof(t_files), 1);
	cmd->files->error = 0;
	if (mini->flags->redirect && mini->flags->redirect->number != 0)
		ft_files(cmd, mini);
}

void	ft_remove_files(t_cmd *cmd, t_mini *mini)
{
	t_cmd	*current;

	current = cmd;
	while (current != NULL)
	{
		ft_select_cmd(current, mini, 0);
		current = current->next;
	}
}

static void	ft_process_file(char *str, int *count, int *check, char **dest)
{
	if (*count > 1)
		(*count)--;
	else if (*count == 1 && *check == 0)
		*dest = ft_strdup(str);
	else if (*count == 1)
		(*count)--;
	if (*dest == NULL)
		return ;
}

void	ft_select_files(t_cmd *cmd, int i)
{
	t_cmd	*current;
	t_type	*type;

	current = cmd;
	while (current != NULL)
	{
		i = -1;
		type = current->type;
		while (current->files->f_order && current->files->f_order[++i] != NULL)
		{
			if (ft_strnstr("1", current->files->order[i], 1) != NULL)
				ft_process_file(current->files->f_order[i],
					&type->infile, &type->here_doc, &type->in);
			if (ft_strnstr("2", current->files->order[i], 1) != NULL)
				ft_process_file(current->files->f_order[i],
					&type->outfile, &type->append, &type->out);
			if (ft_strnstr("3", current->files->order[i], 1) != NULL)
				ft_process_file(current->files->f_order[i],
					&type->here_doc, &type->infile, &type->in);
			if (ft_strnstr("4", current->files->order[i], 1) != NULL)
				ft_process_file(current->files->f_order[i],
					&type->append, &type->outfile, &type->out);
		}
		current = current->next;
	}
}
