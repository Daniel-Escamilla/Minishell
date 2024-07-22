/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands-3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:07:14 by user              #+#    #+#             */
/*   Updated: 2024/06/29 11:14:05 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_nothing_r(char *input, int i)
{
	while (i >= 0 && input[i] && input[i] == ' ')
		i--;
	if (i == 0)
		return (1);
	return (0);
}

int	ft_nothing(char *input, int i)
{
	while (input[i] && input[i] == ' ')
		i++;
	if (input[i] == '\0')
		return (1);
	return (0);
}

int	ft_process_quotes(char *input, int *i, int *first)
{
	int	j;

	j = *i;
	while (input[*i] == 34 || input[*i] == 39)
		*i = ft_locate_next_quote(*i + 1, input, input[*i]) + 1;
	while (j++ < *i)
		(*first)++;
	return (*i);
}

int	ft_find_char(char *input, int i)
{
	while (input[i] == ' ')
		i++;
	return (i);
}
