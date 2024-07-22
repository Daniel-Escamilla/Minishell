/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:52:46 by smarin-a          #+#    #+#             */
/*   Updated: 2024/07/12 09:52:08 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_check_input(t_mini *mini, char *input)
{
	char	**lines;

	mini->flags->locate_red = ft_count_redirect(mini, input);
	if (mini->flags->locate_red == -1)
		return (NULL);
	mini->flags->quote = ft_check_quote(input, 2, 2, mini);
	if (mini->flags->quote == -1)
		return (NULL);
	mini->flags->pipe = ft_count_pipes(input);
	if (mini->flags->pipe == -1)
		return (NULL);
	if (mini->flags->pipe > 0)
	{
		lines = ft_split_pipe(input, '|'); // ls -a > as | wc -l | cat > asd < infile | cat >out -e | << EOF >> FILE
		if (*(lines) == NULL)
			return (NULL);
	}
	return (lines);
}
