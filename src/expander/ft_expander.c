/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:20:46 by descamil          #+#    #+#             */
/*   Updated: 2024/10/13 03:53:05 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

static int	ft_minus_dolar(char *div)
{
	int	i;

	i = 0;
	while (div && div[i])
	{
		if (div[i++] == '$')
		{
			while (div[i])
				if (div[i++] == '$')
					return (1);
			return (0);
		}
	}
	return (0);
}

static int	expand_loop(char **tmp, int *iter, char **env, int *stop)
{
	char	*new_tmp;

	new_tmp = expand_div(iter, *tmp, env, stop);
	free(*tmp);
	*tmp = ft_strdup(new_tmp);
	free(new_tmp);
	if (ft_strchr(*tmp, '$') != NULL && (*tmp)[ft_strlen(*tmp) - 1] == '$'
			&& ft_minus_dolar(*tmp) == 0)
		*iter = -2;
	if (ft_strncmp(*tmp, "$$", 2) == 0 && ft_strlen(*tmp) == 2)
		*iter = -2;
	if (*iter == -2)
		return (1);
	return (0);
}

char	*ft_expander(char **env, char *str)
{
	char	*cpy;
	char	*tmp;
	int		iter;
	int		stop;

	stop = 0;
	iter = -1;
	if (str == NULL)
		return (NULL);
	cpy = ft_strdup(str);
	tmp = ft_strdup(str);
	while (1)
		if (expand_loop(&tmp, &iter, env, &stop))
			break ;
	if (str && iter != 1 && (int)ft_strlen(str) != 0
		&& ft_strncmp(str, cpy, ft_strlen(cpy)) != 0)
		free(str);
	free(cpy);
	return (tmp);
}
