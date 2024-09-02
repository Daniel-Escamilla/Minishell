/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:01:27 by sergio            #+#    #+#             */
/*   Updated: 2024/09/01 09:04:06 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_strjoin(const char *s1, const char *s2)
// {
// 	char	*result;
// 	size_t	len1;
// 	size_t	len2;

// 	len1 = ft_strlen(s1);
// 	len2 = ft_strlen(s2);
// 	result = malloc(len1 + len2 + 1);
// 	if (result)
// 	{
// 		ft_memcpy(result, s1, len1);
// 		ft_memcpy(result + len1, s2, len2 + 1);
// 	}
// 	return (result);
// }

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	n;
	char	*ptr;
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	n = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	ptr = ft_calloc(n + 1, 1);
	if (ptr == NULL)
		return (NULL);
	while ((char)s1[++i] != '\0')
		ptr[i] = (char)s1[i];
	while ((char)s2[j] != '\0')
		ptr[i++] = (char)s2[j++];
	ptr[i] = '\0';
	return (ptr);
}
