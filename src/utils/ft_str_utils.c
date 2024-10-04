/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 08:56:10 by descamil          #+#    #+#             */
/*   Updated: 2024/10/04 23:25:27 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

char	**ft_strstr_dup(char **str)
{
	char	**dup;
	size_t	i;

	i = 0;
	dup = NULL;
	if (str == NULL)
		return (NULL);
	dup = (char **)ft_calloc(sizeof(char *), ft_strstr_len(str) + 1);
	if (dup == NULL)
		return (NULL);
	while (i < ft_strstr_len(str))
	{
		dup[i] = ft_strdup(str[i]);
		if (dup[i] == NULL)
		{
			ft_strstr_free(dup);
			return (NULL);
		}
		i++;
	}
	return (dup);
}

int	ft_strnstrstr(char **str, char *locate)
{
	int	i;
	int	total;

	i = 0;
	total = 0;
	if (str)
	{
		while (str[i])
		{
			if (ft_strncmp(str[i], locate, ft_strlen(locate)) == 0)
				total++;
			i++;
		}
	}
	return (total);
}

size_t	ft_strstr_len(char **str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != NULL)
		i++;
	return (i);
}

char	**ft_strstr_join(char **str, char **str1)
{
	char	**string;
	size_t		size;
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	if (str == NULL)
	{
		string = ft_calloc(sizeof(char *), ft_strstr_len(str1) + 1);
		while (i != ft_strstr_len(str1) && str[i] != NULL)
			string[j++] = ft_strdup(str1[i++]);
		return (string);
	}
	size = ft_strstr_len(str) + ft_strstr_len(str1);
	string = ft_calloc(sizeof(char *), size + 1);
	if (string == NULL)
		return (NULL);
	while (i != ft_strstr_len(str) && str[i] != NULL)
		string[j++] = ft_strdup(str[i++]);
	i = 0;
	while (i != ft_strstr_len(str1) && str1[i] != NULL)
		string[j++] = ft_strdup(str1[i++]);
	string[j] = NULL;
	return (string);
}

void	ft_strstr_free(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
			free(str[i++]);
		free(str);
	}
}
