/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_operators.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:48:53 by smarin-a          #+#    #+#             */
/*   Updated: 2024/06/27 18:45:45 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_search_next_char(char *str, char c, int j)
{
	int	i;

	i = -1;
	while (str[++i] && str[i + 1])
	{
		if (str[i] == 34)
		{
			while (str[++i] != 34)
			{
				if (str[i] == '$' && i >= j)
					return (i);
			}
		}
		if (str[i] == 39)
		{
			i++;
			i = ft_locate_next_quote(i, str, 39);
		}
		if (str[i] == c && i >= j)
			return (i);
	}
	return (0);
}

int	ft_check_special_char(char c)
{
	if (c == '=' || c == '@' || c == '#' || c == '-' || c == '+' || c == '{'
		|| c == '}' || c == '[' || c == ']' || c == '!' || c == '~' || c == '?'
		|| c == '%' || c == '^' || c == '=' || c == '*' || c == '/' || c == '$'
		|| c == ';')
		return (-1);
	return (0);
}

int	ft_is_not_mayor_n_minor_char(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

char	ft_type_of_operator_char(int n)
{
	if (n == 1 || n == 2 || n == 5 || n == 6)
		return ('>');
	else if (n == 3 || n == 4)
		return ('<');
	return (0);
}
