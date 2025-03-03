/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarin-a <smarin-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:52:46 by smarin-a          #+#    #+#             */
/*   Updated: 2025/03/03 13:12:35 by smarin-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static int	ft_negative_error(t_mini *mini)
{
	int	r;
	int	q;
	int	p;
	int	negative;

	negative = 0;
	r = mini->flags->locate_red;
	q = mini->flags->quote;
	p = mini->flags->pipe;
	printf("Negative pipe %d\n", mini->flags->pipe);
	if (r < 0)
		negative = r;
	if (q < 0 && (negative == 0 || q > negative))
		negative = q;
	if (p < 0 && (negative == 0 || p > negative))
		negative = p;
	return (negative);
}

int	ft_error_rqp(t_mini *mini, char *input)
{
	int	negative;
	int	r;
	int	q;
	int	p;

	r = mini->flags->locate_red;
	q = mini->flags->quote;
	p = mini->flags->pipe;
	negative = ft_negative_error(mini);
	if (negative == 0)
		return (0);
	if (negative == r)
		ft_red_error(mini, input);
	if (negative == q)
		printf("dquote>\n");
	if (negative == p)
		printf("mini: syntax error near unexpected token `|'\n");
	mini->error = -2;
	g_exit_status = 2;
	return (1);
}

char	**ft_check_input(t_mini *mini, char *input)
{
	char	**lines;

	lines = NULL;
	mini->flags->locate_red = ft_count_redirect(mini, input, 0, 0);
	mini->flags->quote = ft_check_quote(input, 2, 2, mini);
	mini->flags->pipe = ft_count_pipes(input, 0, 0, 0);
	if (mini->flags->locate_red < 0 || mini->flags->quote < 0
		|| mini->flags->pipe < 0)
		return (NULL);
	if (mini->flags->pipe > 0)
	{
		lines = ft_split_pipe(input, '|');
		if (*(lines) == NULL)
			return (NULL);
	}
	return (lines);
}
