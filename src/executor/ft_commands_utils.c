/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarin-a <smarin-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:07:14 by user              #+#    #+#             */
/*   Updated: 2025/03/03 13:19:16 by smarin-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

void	ft_plus_one(int value1, int value2)
{
	value1 += 1;
	value2 += 1;
}

int	ft_nothing_r(char *input, int i)
{
	if (i == -1)
		return (0);
	while (i >= 0 && input[i] && input[i] == ' ')
		i--;
	if (i == -1)
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
