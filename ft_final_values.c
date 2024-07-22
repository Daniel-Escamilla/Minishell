/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_final_values.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:24:29 by descamil          #+#    #+#             */
/*   Updated: 2024/07/22 12:20:07 by descamil         ###   ########.fr       */
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
			printf("mini: syntax error near unexpected token `%s'\n", cmd->args[i + 1]);
			return (-1);
		}
		i++;
	}
	return (0);
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
		}
	}
	return (order);
}

int	ft_mem_files(t_mini *mini, t_cmd *cmd)
{
	if (mini->flags->redirect && mini->flags->redirect->number > 0)
	{
		cmd->files->f_order = (char **)ft_calloc(sizeof(char *), mini->flags->redirect->number + 1); // FILES
		if (cmd->files->f_order == NULL)
			return (-1);
	}
	return (0);
}

int	ft_pos_files(t_cmd *cmd, int i)
{
	int	files;

	files = 0;
	ft_strstr_printf(cmd->args);
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
	if (files->error == -1)
		return ;
	if (cmd->args)
	{
		if (ft_mem_files(mini, cmd) == -1)
		{
			files->error = -1;
			return ; // MALLOC ERROR;
		}
		if (ft_pos_files(cmd, 0) == -1)
		{
			files->error = -1;
			return ;
		}
	}
}