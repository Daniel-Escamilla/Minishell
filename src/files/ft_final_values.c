/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_final_values.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:24:29 by descamil          #+#    #+#             */
/*   Updated: 2024/10/04 23:29:42 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/files.h"

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

static int	ft_check_dups(t_cmd *cmd)
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

static void	ft_type_file(t_cmd *cmd, int type)
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
	order = (char **)ft_calloc(sizeof(char *),
			(size_t)mini->flags->redirect->number + 1);
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

int	ft_num_files(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd->args && cmd->args[i] != NULL)
	{
		while (ft_type(cmd->args[i]) > 0)
			ft_plus_one(i++, j++);
		if (cmd->args[i] == NULL)
			return (j);
		i++;
	}
	return (j);
}
