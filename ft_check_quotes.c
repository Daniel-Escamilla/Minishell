/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:55:56 by smarin-a          #+#    #+#             */
/*   Updated: 2024/07/09 16:59:31 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_locate_next_quote(int i, char *input, char quote)
{
	while (input[i] && input[i] != quote)
		i++;
	return (i);
}

int	ft_check_quote_pairs(char *input, int *i, char quote)
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

int	ft_check_quote(char *input, int simp_quote, int doub_quote, t_mini *mini)
{
	int	i;
	
	i = -1;
	while (input[++i])
	{
		if (input[i] == 39)
			simp_quote += ft_check_quote_pairs(input, &i, input[i]);
		if (input[i] == 34)
			doub_quote += ft_check_quote_pairs(input, &i, input[i]);
		if (simp_quote % 2 == 1 || doub_quote % 2 == 1)
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
