/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:04:59 by descamil          #+#    #+#             */
/*   Updated: 2024/07/12 10:20:50 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen_pipe(const char *s, int i, char c)
{
	int	len;
	int	j;

	len = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	while (s[i] != '\0' && s[i] != c)
	{
    	j = i;
		if (s[i] == '\'' || s[i] == '\"')
		{
			i = ft_locate_next_quote(i + 1, (char *)s, s[i]) + 1;
			if (j != i)
				len += i - j;
		}
		else
			ft_plus_one(i++, len++);
	}
	// printf(B_BL_1"LEN --> %d\n"RESET, len);
	return (len);
}

char	*ft_strlcpy_pipe(char *s, char c, int *new_start, int size)
{
	char	*ptr;
	int		j;
	int		start;

	j = 0;
	start = *new_start;
	ptr = (char *)malloc(size + 1);
	if (ptr == NULL)
		return (NULL);
	while (s[start] == c && s[start] != '\0')
		start++;
	while (s[start] != '\0' && j < size)
		ptr[j++] = s[start++];
	ptr[j] = '\0';
	*new_start = start;
	// printf(B_YE_0"PTR --> %s\n"RESET, ptr);
	return (ptr);
}

void	*free_memory_pipe(int a, char **arr)
{
	int	f;

	f = 0;
	while (f < a)
		free(arr[f++]);
	free(arr);
	return (NULL);
}

char	**ft_split_pipe(const char *s, char c)
{
	int		i;
	int		a;
	int		len_mod;
	char	**arr;
	char	*cpy_mod;

	i = 0;
	a = 0;
	len_mod = 0;
	arr = (char **)ft_calloc((ft_count_pipes((char *)s) + 2), sizeof(char *));
	if (arr == NULL)
		return (NULL);
	while (a < ft_count_pipes((char *)s) + 1)
	{
		len_mod = ft_strlen_pipe(s, i, c);
		cpy_mod = ft_strlcpy_pipe((char *)s, c, &i, len_mod);
		if (cpy_mod == NULL)
			return (free_memory_pipe(a, arr));
		arr[a++] = cpy_mod;
	}
	// ft_strstr_printf(arr);
	return (arr);
}
