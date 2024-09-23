/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:20:46 by descamil          #+#    #+#             */
/*   Updated: 2024/09/23 12:04:31 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

char	*ft_expander(char **env, char *str)
{
	char	*cpy;
	char	*div;
	char	*tmp;
	int		iter;

	iter = -1;
	if (str == NULL)
		return (NULL);
	cpy = ft_strdup(str);
	tmp = ft_strdup(str);
	while (1)
	{
		div = expand_div(&iter, tmp, env);
		free(tmp);
		if (iter == -2)
			break ;
		tmp = ft_strdup(div);
		free(div);
		div = NULL;
	}
	if (str && iter != 1 && (int)ft_strlen(str) != 0
		&& ft_strncmp(str, cpy, ft_strlen(cpy)) != 0)
		free(str);
	free(cpy);
	return (div);
}
