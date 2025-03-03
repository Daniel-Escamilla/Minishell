/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarin-a <smarin-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:22:30 by smarin-a          #+#    #+#             */
/*   Updated: 2025/03/03 13:14:28 by smarin-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static int	ft_pipe_error(char *input, int i)
{
	while (input[i] != '\0')
	{
		while (input[i] == ' ')
			i++;
		if (input[i] == '|' || input[i] == '\0')
			return (-1);
		return (1);
	}
	return (-1);
}

int	ft_count_pipes(char *input, int amount, int character, int i)
{
	while (input[i])
	{
		if (input[i] == '|')
		{
			character = ft_pipe_error(input, i + 1);
			printf("char %d\n", character);
			amount++;
		}
		printf("NOTHING_R --> %d\n", ft_nothing_r(input, i - 1) == 1);
		if (character == -1 || (input[i] == '|' && (input[i + 1] == '|'
					|| input[i + 1] == '\0' || ft_nothing(input, i + 1) == 1
					|| ft_nothing_r(input, i - 1) == 1)) || input[0] == '|')
			return ((i + 1) * -1);
		if (input[i] == '\0')
			return (amount);
		if (input[i] == '\'' || input[i] == '\"')
		{
			i = ft_locate_next_quote(i + 1, input, input[i]);
			if (input[i] == '\0')
				return (amount);
		}
		i++;
	}
	return (amount);
}
