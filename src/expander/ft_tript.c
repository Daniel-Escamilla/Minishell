/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tript.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:13:06 by user              #+#    #+#             */
/*   Updated: 2024/10/22 17:07:19 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

static void	ft_free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (i < 3)
		free(arr[i++]);
	free(arr);
}

static char	*ft_extract_start(char *str, int start)
{
	char	*result;
	int		i;

	i = -1;
	if (start == 0)
		return (NULL);
	result = ft_calloc(sizeof(char), (size_t)start + 1);
	if (result == NULL)
		return (NULL);
	while (++i < start)
		result[i] = str[i];
	return (result);
}

static char	*ft_extract_middle(char *str, int size, int start)
{
	char	*result;
	int		i;

	i = -1;
	result = ft_calloc(sizeof(char), (size_t)size + 1);
	if (result == NULL)
		return (NULL);
	while (++i < size)
		result[i] = str[start + i];
	return (result);
}

static char	*ft_extract_end(char *str, int size, int start)
{
	char	*result;
	int		len;
	int		i;

	i = -1;
	len = (int)ft_strlen(str) - start - size;
	if (len <= 0)
		return (NULL);
	result = ft_calloc(sizeof(char), (size_t)len + 1);
	if (result == NULL)
		return (NULL);
	while (++i < len)
		result[i] = str[start + size + i];
	return (result);
}

char	**ft_tript(char *str, int size, int start)
{
	char	**div;

	if (size == -1)
		size = 1;
	div = (char **)ft_calloc(sizeof(char *), 4);
	if (div == NULL)
		return (NULL);
	div[0] = ft_extract_start(str, start);
	div[1] = ft_extract_middle(str, size, start);
	div[2] = ft_extract_end(str, size, start);
	if ((start != 0 && div[0] == NULL) || div[1] == NULL)
	{
		ft_free_array(div);
		return (NULL);
	}
	return (div);
}
