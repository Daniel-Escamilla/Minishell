/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:00:37 by user              #+#    #+#             */
/*   Updated: 2024/09/11 23:16:09 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_select_cmd(t_cmd *current, t_mini *mini, int j)
// {
// 	char	**tmp2;
// 	char	**tmp;
// 	int		size;
// 	int		i;

// 	i = -1;
// 	size = 0;
// 	tmp = ft_strstr_dup(current->args);
// 	if (tmp == NULL)
// 		mini->cmd->files->error = -1;
// 	while (tmp[++i])
// 	{
// 		if (ft_type(tmp[i]) != 0)
// 			size++;
// 	}
// 	i = -1;
// 	tmp2 = ft_calloc(sizeof(char *), ft_strstr_len(current->args) - (size * 2) + 1);
// 	if (tmp2 == NULL)
// 		mini->cmd->files->error = -1;
// 	while (tmp[++i])
// 	{
// 		current->error = 0;
// 		if (ft_type(tmp[i]) != 0)
// 			i++;
// 		else
// 		{
// 			if (j == 0)
// 			{
// 				current->cmd = ft_builtins(current, tmp[i]);
// 				if (current->cmd == NULL)
// 					current->cmd = ft_route_cmd(mini, current, tmp[i]);
// 				if (current->cmd == NULL && current->error != -2)
// 					mini->cmd->files->error = -1;
// 			}
// 			if (current->error != -2 && j < ft_strstr_len(current->args) - (size * 2))
// 			{
// 				tmp2[j] = ft_strdup(tmp[i]);
// 				if (tmp2[j++] == NULL)
// 					mini->cmd->files->error = -1;
// 			}
// 		}
// 	}
// 	ft_strstr_free(current->args);
// 	current->args = NULL;
// 	current->args = ft_strstr_dup(tmp2);
// 	if (current->args == NULL)
// 		mini->cmd->files->error = -1;
// 	ft_strstr_free(tmp2);
// 	ft_strstr_free(tmp);
// }

static void	ft_initialize_selection(t_cmd *current)
{
	int		i;
	char	**tmp;

	i = -1;
	current->size = 0;
	current->error = 0;
	tmp = ft_strstr_dup(current->args);
	ft_strstr_printf(tmp);
	if (tmp == NULL)
		current->files->error = -1;
	while (tmp[++i])
		if (ft_type(tmp[i]) != 0)
			current->size++;
	current->tmp = tmp;
}

static char	**ft_allocate_tmp2(t_cmd *current)
{
	char	**tmp2;
	int		arg_len;

	arg_len = ft_strstr_len(current->args);
	tmp2 = ft_calloc(sizeof(char *), arg_len - (current->size * 2) + 1);
	if (tmp2 == NULL)
		current->files->error = -1;
	return (tmp2);
}

static void	ft_process_command(t_cmd *current, t_mini *mini, char *arg)
{
	current->cmd = ft_builtins(current, arg);
	if (current->cmd == NULL)
		current->cmd = ft_route_cmd(mini, current, arg);
	if (current->cmd == NULL && current->error != -2)
		current->files->error = -3;
}

static void	ft_process_argument(t_cmd *current, char ***tmp2, char *arg, int *j)
{
	int	max_args;

	max_args = ft_strstr_len(current->args) - (current->size * 2);
	
	printf(B_CY_0"Size %d * 2\n", current->size);
	ft_strstr_printf(current->args);
	printf(B_OR_2"%d - %d\n"RESET, ft_strstr_len(current->args), current->size * 2);
	if (current->files->error != -2 && *j < max_args)
	{
		*(tmp2)[*j] = ft_strdup(arg);
		if (*(tmp2)[(*j)++] == NULL)
			current->files->error = -1;
	}
}

void	ft_select_cmd(t_cmd *current, t_mini *mini, int j)
{
	char	**tmp2;
	int		i;

	ft_initialize_selection(current);
	tmp2 = ft_allocate_tmp2(current);
	i = -1;
	while (current->tmp[++i])
	{
		current->error = 0;
		if (ft_type(current->tmp[i]) != 0)
			i++;
		else
		{
			if (j == 0)
				ft_process_command(current, mini, current->tmp[i]);
			ft_process_argument(current, &tmp2, current->tmp[i], &j);
		}
	}
	ft_strstr_free(current->args);
	current->args = NULL;
	current->args = ft_strstr_dup(tmp2);
	if (current->args == NULL)
		current->files->error = -1;
	ft_strstr_free(tmp2);
	ft_strstr_free(current->tmp);
}
