/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:14:41 by user              #+#    #+#             */
/*   Updated: 2025/02/27 16:04:23 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

char	*ft_dolar_to_iqual(char *div)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if (ft_strncmp(div, "$", 1) == 0 && ft_strlen(div) == 1)
		return (div);
	while (div[j] != '\0')
		div[i++] = div[j++];
	if (div[j] == '\0')
		div[i] = '=';
	return (div);
}

char	*ft_join(char **div, char *tmp)
{
	char	*ptr;
	char	*final;

	final = NULL;
	if (div[0] == NULL && div[2] == NULL)
	{
		final = ft_calloc(sizeof(char), ft_strlen(tmp) + 1);
		ft_strlcpy(final, tmp, ft_strlen(tmp) + 1);
	}
	else if (div[0] != NULL && div[2] == NULL)
		final = ft_strjoin(div[0], tmp);
	else if (div[2] != NULL && div[0] == NULL)
		final = ft_strjoin(tmp, div[2]);
	else
	{
		ptr = ft_strjoin(div[0], tmp);
		if (ptr != NULL)
		{
			final = ft_strjoin(ptr, div[2]);
			free(ptr);
		}
	}
	if (final)
		return (final);
	return (tmp);
}

int	ft_is_special_char(char c)
{
	unsigned char uc = (unsigned char)c;
	if ((uc >= 33 && uc <= 126 &&
		(uc == '$' || uc == '*' || uc == '?' || uc == '"' || uc == '\'' ||
		uc == '`' || uc == '\\' || uc == '|' || uc == '&' || uc == ';' ||
		uc == '>' || uc == '<' || uc == '(' || uc == ')' || uc == '{' ||
		uc == '}' || uc == '[' || uc == ']' || uc == '!' || uc == '#' ||
		uc == ':' || uc == ',' || uc == '%' || uc == '@' || uc == '/' ||
		uc == '^' || uc == '~' || uc == '+' || uc == '-')) ||
		uc == 0xBF || uc == 0xA1)
		return (1);
	return (0);
}

int	ft_size_var(char *str)
{
	int	i;

	i = 1;
	if (str[i] == '$' || str[i] == '?')
		return (++i);
	if (str[i] == '\0' || str[i] == ' ')
		return (-1);
	while (str[i] != '\0' && str[i] != ' ' &&
		ft_is_special_char(str[i]) == 0 && str[i] != '=')
		i++;
	return (i);
}
