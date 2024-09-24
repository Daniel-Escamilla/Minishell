/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:20:46 by descamil          #+#    #+#             */
/*   Updated: 2024/09/24 17:35:48 by user             ###   ########.fr       */
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
		if (ft_strchr(div, '$') != NULL && div[ft_strlen(div) -1 ] == '$')
			iter = -2;
		if (ft_strncmp(tmp, "$$", 2) == 0 && ft_strlen(tmp) == 2)
			iter = -2;
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
