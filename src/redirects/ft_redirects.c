/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:31:41 by descamil          #+#    #+#             */
/*   Updated: 2025/02/21 13:26:09 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/redirects.h"

void	ft_red_error(t_mini *mini, char *input)
{
	mini->flags->locate_red *= -1;
	if (mini->flags->redirect->red_error != 0)
	{
		if (mini->flags->redirect->red_error < 3)
		{
			if (mini->flags->redirect->red_error == 1)
				mini->flags->redirect->error
					= ft_substr(input, (unsigned)mini->flags->locate_red, 1);
			else if (mini->flags->redirect->red_error == 2)
				mini->flags->redirect->error = ft_substr(input,
						1 + (unsigned)mini->flags->locate_red, 1);
		}
		else if (mini->flags->redirect->red_error > 2)
		{
			if (mini->flags->redirect->red_error == 3)
				mini->flags->redirect->error
					= ft_substr(input, (unsigned)mini->flags->locate_red, 2);
			else if (mini->flags->redirect->red_error == 4)
				mini->flags->redirect->error = ft_substr(input,
						1 + (unsigned)mini->flags->locate_red, 2);
		}
		printf("mini: parse error near `%s'\n", mini->flags->redirect->error);
		free(mini->flags->redirect->error);
	}
	return ;
}

static void	ft_start_red(t_mini *mini)
{
	mini->flags->redirect = ft_calloc(sizeof(t_red), 1);
	if (mini->flags->redirect == NULL)
		return ;
	mini->flags->redirect->do_le = 0;
	mini->flags->redirect->do_ri = 0;
	mini->flags->redirect->si_le = 0;
	mini->flags->redirect->si_ri = 0;
	mini->flags->redirect->number = 0;
}

static int	ft_red(char *input)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (input[++i] != '\0')
	{
		if (input[i] == '<' || input[i] == '>')
			j++;
	}
	return (j);
}

static int	ft_redirect_size(t_mini *mini, char *input, int *i)
{
	int	size;

	size = 0;
	while (input[*i] == '<' || input[*i] == '>')
		ft_plus_one((*i)++, size++);
	if (size == 1)
		ft_one(mini, &input[*i - size]);
	else if (size == 2)
		ft_two(mini, &input[*i - size]);
	else if (size == 3)
		ft_three(mini, &input[*i - size]);
	else if (size >= 4)
		ft_four_plus(mini, &input[*i - size]);
	return (size);
}

int	ft_count_redirect(t_mini *mini, char *input, int i, int size)
{
	if (ft_red(input) != 0)
	{
		ft_start_red(mini);
		if (mini->flags->redirect == NULL)
			return (-1);
		while (input[i] != '\0')
		{
			if (input[i] == '\'' || input[i] == '\"')
				i = ft_locate_next_quote(i + 1, input, input[i]);
			size = ft_redirect_size(mini, input, &i);
			if (mini->flags->redirect->red_error != 0 || input[i++] == '\0')
				break ;
		}
		if (mini->flags->redirect->red_error > 0)
		{
			mini->error = -2;
			return ((i - size + 1) * -1);
		}
		mini->flags->redirect->number = ft_red_count(mini);
	}
	return (i - size);
}
