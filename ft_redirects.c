/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:31:41 by descamil          #+#    #+#             */
/*   Updated: 2024/09/09 10:56:31 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_red_error(t_mini *mini, char *input)
{
	if (mini->flags->redirect->red_error != 0)
	{
		if (mini->flags->redirect->red_error < 3)
		{
			if (mini->flags->redirect->red_error == 1)
				mini->flags->redirect->error
					= ft_substr(input, mini->flags->locate_red, 1);
			else if ((mini->flags->redirect->red_error == 2))
				mini->flags->redirect->error
					= ft_substr(input, 1 + mini->flags->locate_red, 1);
		}
		else if (mini->flags->redirect->red_error > 2)
		{
			if (mini->flags->redirect->red_error == 3)
				mini->flags->redirect->error
					= ft_substr(input, mini->flags->locate_red, 2);
			else if ((mini->flags->redirect->red_error == 4))
				mini->flags->redirect->error
					= ft_substr(input, 1 + mini->flags->locate_red, 2);
		}
		printf("mini: parse error near `%s'\n", mini->flags->redirect->error);
		free(mini->flags->redirect->error);
		return ;
	}
	return ;
}

void	ft_start_red(t_mini *mini)
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

int	ft_red(char *input)
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

int	ft_redirect_size(t_mini *mini, char *input, int *i)
{
	int	size;

	size = 0;
	mini->flags->redirect->red_error = 0;
	while ((input[*i] == '<' || input[*i] == '>') && *i++ >= size)
		size++;
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

int	ft_count_redirect(t_mini *mini, char *input, int i)
{
	int	size;

	size = 0;
	if (ft_red(input) != 0)
	{
		ft_start_red(mini);
		if (mini->flags->redirect == NULL)
			return (0);
		while (input[++i - 1] != '\0')
		{
			if (input[i] == '\'' || input[i] == '\"')
				i = ft_locate_next_quote(i + 1, input, input[i]);
			size = ft_redirect_size(mini, input, &i);
			if (input[i] == '\0' || mini->flags->redirect->red_error != 0)
				break ;
		}
		if (mini->flags->redirect->red_error > 0)
		{
			mini->flags->locate_red = (i - size + 1);
			ft_red_error(mini, input);
			return (-1);
		}
		mini->flags->redirect->number = ft_red_count(mini);
	}
	return (i - size);
}
