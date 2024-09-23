/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:52:46 by smarin-a          #+#    #+#             */
/*   Updated: 2024/09/21 12:27:27 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

char	**ft_check_input(t_mini *mini, char *input)
{
	char	**lines;

	lines = NULL;
	mini->flags->locate_red = ft_count_redirect(mini, input, 0);
	if (mini->flags->locate_red == -1)
		return (NULL);
	mini->flags->quote = ft_check_quote(input, 2, 2, mini);
	if (mini->flags->quote == -1)
		return (NULL);
	mini->flags->pipe = ft_count_pipes(input, 0, 0);
	if (mini->flags->pipe == -1)
		return (NULL);
	if (mini->flags->pipe > 0)
	{
		lines = ft_split_pipe(input, '|');
		if (*(lines) == NULL)
			return (NULL);
	}
	return (lines);
}
