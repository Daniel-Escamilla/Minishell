/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:14:04 by user              #+#    #+#             */
/*   Updated: 2024/09/16 16:21:36 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_change_var(char *div, char **env)
{
	char	*str;
	int		i;

	i = -1;
	str = NULL;
	if (div && ft_strlen(div) == 1 && ft_strncmp(div, "$", 1) == 0)
		return(ft_strdup("$"));
	while (env[++i] != NULL)
	{
		if (ft_strnstr(env[i], div, ft_strlen(div)) != NULL)
		{
			if (str)
				free(str);
			str = ft_calloc(sizeof(char),
					ft_strlen(env[i]) - ft_strlen(div) + 1);
			if (str == NULL)
				return (NULL);
			ft_memcpy(str, env[i] + ft_strlen(div),
				ft_strlen(env[i]) - ft_strlen(div) + 1);
			if (str != NULL)
				return (str);
		}
	}
	return ("");
}
