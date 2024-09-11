/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:20:46 by descamil          #+#    #+#             */
/*   Updated: 2024/09/11 17:27:47 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expander(char **env, char *str)
{
	char	*cpy;
	char	*div;
	int		iter;

	iter = -1;
	if (str == NULL)
		return (NULL);
	cpy = ft_strdup(str);
	while (1)
	{
		div = expand_div(&iter, &str, env);
		if (iter == -2)
			break ;
	}
	if (str && iter != 1 && (int)ft_strlen(str) != 0
		&& ft_strncmp(str, cpy, ft_strlen(cpy)) != 0)
		free(str);
	free(cpy);
	return (div);
}
