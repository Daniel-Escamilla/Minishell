/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:14:04 by user              #+#    #+#             */
/*   Updated: 2024/10/24 12:01:19 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

char	*ft_change_var(char *div, char **env, int i)
{
	char	*str;

	i = -1;
	str = NULL;
	if (div && ft_strlen(div) == 1 && ft_strncmp(div, "$", 1) == 0)
		return (ft_strdup("$"));
	if (div && ft_strlen(div) == 2 && ft_strncmp(div, "?=", 2) == 0)
		return (ft_itoa(g_exit_status));
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
