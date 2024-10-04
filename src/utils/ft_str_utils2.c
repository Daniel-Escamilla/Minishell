/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 09:30:16 by descamil          #+#    #+#             */
/*   Updated: 2024/10/04 23:28:28 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

char	*ft_strchr_mod(char *str, int value, int stop)
{
	char	quote;
	int		i;

	i = -1;
	quote = 0;
	while (str[++i] != '\0')
	{
		if (str[i] == '\"')
		{
			quote += 1;
			if (quote == 2)
				quote = 0;
		}
		else if (str[i] == '\'' && quote == 0)
		{
			i = ft_locate_next_quote(i + 1, str, str[i]);
			if (str[i] == '\0')
				return (NULL);
		}
		if (str && str[i] == value && stop-- == 0)
			return (str + i);
	}
	return (NULL);
}

char	**ft_sindub_join(char **str, char *str1)
{
	char	**result;
	size_t	len;
	int		i;

	i = (int)-1;
	if (str == NULL)
		len = 0;
	else
		len = ft_strstr_len(str);
	result = ft_calloc(sizeof(char *), len + 1 + 1);
	while (++i < (int)len)
		result[i] = ft_strdup(str[i]);
	result[i] = ft_strdup(str1);
	return (result);
}

int	ft_strlen_dup(char *argv)
{
	int	i;
	int	space;

	i = 0;
	space = 0;
	if (argv)
		while (argv[i] != '\0')
			if (argv[i++] == ' ')
				space++;
	return (i - space);
}

void ft_error_in_child(char *prefix, char *arg, char *suffix)
{
    write(2, prefix, strlen(prefix));
    write(2, arg, strlen(arg));
    write(2, suffix, strlen(suffix));
}