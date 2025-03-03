/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:25:51 by descamil          #+#    #+#             */
/*   Updated: 2025/03/03 17:34:04 by descamil         ###   ########.fr       */
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
		result[i] = ft_expander(mini, tmp[i]);
	ft_strstr_free(tmp);
	return (result);
}

static void	ft_expand_files(t_mini *mini, t_files **files)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = NULL;
	tmp = ft_strstr_dup((*files)->f_order);
	ft_strstr_free((*files)->f_order);
	(*files)->f_order = NULL;
	(*files)->f_order = ft_calloc(sizeof(char *),
			(size_t)ft_strstr_len(tmp) + 1);
	while (tmp[i] != NULL)
	{
		if (atoi((*files)->order[i]) == 3)
			(*files)->f_order[i] = ft_strdup(tmp[i]);
		else
			(*files)->f_order[i] = ft_expander(mini, tmp[i]);
		i++;
	}
	ft_strstr_free(tmp);
}

void	ft_do_expander(t_mini *mini, t_cmd *cmd)
{
	char	**tmp;
	t_cmd	*curr;

	curr = cmd;
	while (curr != NULL)
	{
		if (curr->args)
		{
			tmp = ft_strstr_dup(curr->args);
			ft_strstr_free(curr->args);
			curr->args = NULL;
			curr->args = ft_str_expander(mini, tmp);
		}
		if (curr->files->f_order)
			ft_expand_files(mini, &curr->files);
		curr = curr->next;
	}
}
