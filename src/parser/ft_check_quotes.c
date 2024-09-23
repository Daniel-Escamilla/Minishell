/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:55:56 by smarin-a          #+#    #+#             */
/*   Updated: 2024/09/21 12:27:27 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

int	ft_locate_next_quote(int i, char *input, char quote)
{
	while (input[i] && input[i] != quote)
		i++;
	return (i);
}

static int	ft_check_pairs(char *input, int *i, char quote)
{
	int	count;

	count = 1;
	while (input[*i + 1] && input[*i + 1] != quote)
		(*i)++;
	if (input[*i + 1] == quote)
		count++;
	(*i)++;
	return (count);
}

int	ft_check_quote(char *input, int simp, int doub, t_mini *mini)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == 39)
			simp += ft_check_pairs(input, &i, input[i]);
		if (input[i] == 34)
			doub += ft_check_pairs(input, &i, input[i]);
		if (simp % 2 == 1 || doub % 2 == 1)
		{
			mini->flags->quote = 1;
			printf("dquote>\n");
			return (-1);
		}
		if (input[i] == '\0')
			break ;
	}
	return (1);
}
