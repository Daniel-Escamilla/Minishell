/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_spaces.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:41:47 by descamil          #+#    #+#             */
/*   Updated: 2024/10/24 11:43:39 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static void	ft_split_space_join(char ***result, char *tmp)
{
	char	**copy;
	char	**str;

	str = ft_split(tmp, ' ');
	if (*result == NULL)
		*result = ft_strstr_join(str, NULL);
	else
	{
		copy = ft_strstr_join(*result, str);
		ft_strstr_free(*result);
		*result = copy;
	}
	ft_strstr_free(str);
}

void	ft_quit_spaces(t_cmd **cmd)
{
	char	**result;
	char	**copy;
	char	**tmp;
	int		i;

	i = -1;
	result = NULL;
	tmp = ft_strstr_dup((*cmd)->args);
	while (tmp[++i])
	{
		if (ft_has_quotes(tmp[i], 0) == 0 && ft_strchr(tmp[i], ' '))
			ft_split_space_join(&result, tmp[i]);
		else
		{
			copy = ft_sindub_join(result, tmp[i]);
			ft_strstr_free(result);
			result = copy;
		}
	}
	ft_strstr_free(tmp);
	ft_strstr_free((*cmd)->args);
	(*cmd)->args = result;
}
