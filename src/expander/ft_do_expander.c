/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:25:51 by descamil          #+#    #+#             */
/*   Updated: 2024/10/13 03:56:13 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

static char	**ft_str_expander(t_mini *mini, char **args)
{
	char	**tmp;
	char	**result;
	int		size;
	int		i;

	i = -1;
	result = NULL;
	size = (int)ft_strstr_len(args);
	tmp = ft_strstr_dup(args);
	ft_strstr_free(args);
	result = ft_calloc(sizeof(char *), (size_t)size + 1);
	if (result == NULL)
	{
		ft_strstr_free(tmp);
		return (NULL);
	}
	while (tmp[++i])
		result[i] = ft_expander(mini->env->env, tmp[i]);
	ft_strstr_free(tmp);
	return (result);
}

void	ft_do_expander(t_mini *mini, t_cmd *cmd)
{
	char	**tmp;
	int		i;
	t_cmd	*curr;

	curr = cmd;
	while (curr != NULL)
	{
		i = 0;
		if (curr->args)
		{
			tmp = ft_strstr_dup(curr->args);
			ft_strstr_free(curr->args);
			curr->args = NULL;
			curr->args = ft_str_expander(mini, tmp);
		}
		if (curr->files->f_order)
		{
			tmp = NULL;
			tmp = ft_strstr_dup(curr->files->f_order);
			ft_strstr_free(curr->files->f_order);
			curr->files->f_order = NULL;
			curr->files->f_order = ft_calloc(sizeof(char *),
					(size_t)ft_strstr_len(tmp) + 1);
			while (tmp[i] != NULL)
			{
				if (atoi(curr->files->order[i]) == 3)
					curr->files->f_order[i] = ft_strdup(tmp[i]);
				else
					curr->files->f_order[i]
						= ft_expander(mini->env->env, tmp[i]);
				i++;
			}
			ft_strstr_free(tmp);
		}
		curr = curr->next;
	}
}
