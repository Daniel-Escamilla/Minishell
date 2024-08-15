/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_final_values.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:24:29 by descamil          #+#    #+#             */
/*   Updated: 2024/08/14 19:50:27 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen_dup(char *argv)
{
	int	i;
	int	space;

	i = 0;
	space = 0;
	if (argv)
	{
		while (argv[i] != '\0')
		{
			if (argv[i++] == ' ')
				space++;
		}
	}
	return (i - space);
}

int	ft_type(char *argv)
{
	if (argv == NULL)
		return (0);
	if (ft_strnstr(argv, "<", 1) && (int)ft_strlen_dup(argv) == 1)
		return (1);
	if (ft_strnstr(argv, ">", 1) && (int)ft_strlen_dup(argv) == 1)
		return (2);
	if (ft_strnstr(argv, "<<", 2) && (int)ft_strlen_dup(argv) == 2)
		return (3);
	if (ft_strnstr(argv, ">>", 2) && (int)ft_strlen_dup(argv) == 2)
		return (4);
	return (0);
}

int	ft_check_dups(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args && cmd->args[i + 1])
	{
		if (ft_type(cmd->args[i]) != 0 && ft_type(cmd->args[i + 1]) != 0)
		{
			printf("mini: syntax error near unexpected token `%s'\n",
				cmd->args[i + 1]);
			return (-1);
		}
		i++;
	}
	return (0);
}

void	ft_type_file(t_cmd *cmd, int type)
{
	if (!cmd->type)
	{
		cmd->type = ft_calloc(sizeof(t_type), 1);
		cmd->type->infile = 0;
		cmd->type->outfile = 0;
		cmd->type->here_doc = 0;
		cmd->type->append = 0;
	}
	if (type == 1)
		cmd->type->infile += 1;
	else if (type == 2)
		cmd->type->outfile += 1;
	else if (type == 3)
		cmd->type->here_doc += 1;
	else if (type == 4)
		cmd->type->append += 1;
}

char	**ft_order(t_cmd *cmd, t_mini *mini)
{
	char	**order;
	int		i;
	int		j;

	i = -1;
	j = 0;
	order = ft_calloc(sizeof(char *), mini->flags->redirect->number + 1);
	if (order == NULL)
		return (NULL);
	if (ft_check_dups(cmd) == -1)
	{
		mini->cmd->files->error = -1;
		return (NULL);
	}
	if (cmd->args)
	{
		while (cmd->args[++i])
		{
			if (ft_type(cmd->args[i]) != 0)
				order[j++] = ft_itoa(ft_type(cmd->args[i]));
			ft_type_file(cmd, ft_type(cmd->args[i]));
		}
	}
	return (order);
}

int	ft_mem_files(t_mini *mini, t_cmd *cmd)
{
	if (mini->flags->redirect && mini->flags->redirect->number > 0)
	{
		cmd->files->f_order = (char **)ft_calloc(sizeof(char *),
				mini->flags->redirect->number + 1);
		if (cmd->files->f_order == NULL)
			return (-1);
	}
	return (0);
}

int	ft_pos_files(t_cmd *cmd, int i)
{
	int	files;

	files = 0;
	while (cmd->args[i])
	{
		if (ft_type(cmd->args[i]) > 0)
		{
			if (cmd->args[i + 1] == NULL)
			{
				printf("mini: syntax error near unexpected token `newline'\n");
				return (-1);
			}
			cmd->files->f_order[files++] = ft_strdup(cmd->args[i + 1]);
		}
		i++;
	}
	return (0);
}

void	ft_files(t_cmd *cmd, t_mini *mini, t_files *files)
{
	if (mini->flags->redirect && mini->flags->redirect->number > 0)
		files->order = ft_order(cmd, mini);
	if (mini->cmd->files->error == -1)
		return ;
	if (cmd->args)
	{
		if (ft_mem_files(mini, cmd) == -1)
		{
			mini->cmd->files->error = -1;
			return ;
			// MALLOC ERROR
		}
		if (ft_pos_files(cmd, 0) == -1)
		{
			mini->cmd->files->error = -1;
			return ;
		}
	}
}
