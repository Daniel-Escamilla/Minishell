/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:05:18 by user              #+#    #+#             */
/*   Updated: 2024/09/21 12:27:27 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

void	ft_change_env(char ***env, char *variable, char *content)
{
	int		i;
	char	*join;
	char	*new_value;

	i = -1;
	if (content == NULL || variable == NULL)
		return ;
	join = ft_strjoin(variable, "=");
	if (!join)
		return ;
	while ((*env)[++i] != NULL)
	{
		if (ft_strnstr((*env)[i], join, ft_strlen(join)))
		{
			new_value = ft_strjoin(join, content);
			if (!new_value)
				break ;
			free((*env)[i]);
			(*env)[i] = ft_strdup(new_value);
			free(new_value);
			break ;
		}
	}
	free(join);
}
