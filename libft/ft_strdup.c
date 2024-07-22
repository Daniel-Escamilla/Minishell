/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:39:53 by sergio            #+#    #+#             */
/*   Updated: 2024/06/10 11:51:59 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	len;
	char	*copy;

	len = ft_strlen(str);
	copy = (char *)malloc(len + 1);
	if (!copy)
		return (NULL);
	ft_strlcpy(copy, str, len + 1);
	return (copy);
}
