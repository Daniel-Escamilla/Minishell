/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:36:54 by descamil          #+#    #+#             */
/*   Updated: 2024/10/24 11:40:10 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static void	ft_handle_quote_args(t_cmd *cmd, int i)
{
	char	*itoa;
	char	**tmp;

	itoa = ft_itoa(i);
	if (cmd->quote_args == NULL)
		cmd->quote_args = ft_sindub_join(NULL, itoa);
	else
	{
		tmp = ft_strstr_dup(cmd->quote_args);
		ft_strstr_free(cmd->quote_args);
		cmd->quote_args = ft_sindub_join(tmp, itoa);
		ft_strstr_free(tmp);
	}
	free(itoa);
}

static void	ft_do_remove_args_quotes(t_cmd *cmd)
{
	int	*quotes;
	int	i;

	i = 0;
	while (cmd->args && cmd->args[i])
	{
		quotes = ft_find_quotes(cmd->args[i], 0);
		if (quotes[1] != -1)
			ft_handle_quote_args(cmd, i);
		if (quotes[0] != -1 && quotes[1] != -1)
			ft_rm_quotes(&cmd->args[i], quotes);
		else
			free(quotes);
		i++;
	}
}

static void	ft_do_remove_files_quotes(t_cmd *cmd)
{
	int	*quotes;
	int	i;

	i = 0;
	while (cmd->files && cmd->files->f_order && cmd->files->f_order[i])
	{
		if (ft_atoi(cmd->files->order[i]) != 3)
		{
			quotes = ft_find_quotes(cmd->files->f_order[i], 0);
			ft_rm_quotes(&cmd->files->f_order[i], quotes);
			free(quotes);
		}
		i++;
	}
}

void	ft_do_remove_quotes(t_cmd *cmd)
{
	t_cmd	*current;

	current = cmd;
	while (current != NULL)
	{
		ft_do_remove_args_quotes(current);
		ft_do_remove_files_quotes(current);
		current = current->next;
	}
}
