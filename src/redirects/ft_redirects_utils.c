/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirects_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:11:03 by descamil          #+#    #+#             */
/*   Updated: 2024/09/20 23:01:05 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirects.h"

void	ft_one(t_mini *mini, char *input)
{
	if (input[0] == '<')
		mini->flags->redirect->si_le += 1;
	else
		mini->flags->redirect->si_ri += 1;
}

void	ft_two(t_mini *mini, char *input)
{
	if (input[0] == input[1])
	{
		if (input[0] == '<')
			mini->flags->redirect->do_le += 1;
		else
			mini->flags->redirect->do_ri += 1;
	}
	else
		mini->flags->redirect->red_error = 1;
}

void	ft_three(t_mini *mini, char *input)
{
	if (input[0] == input[1])
		mini->flags->redirect->red_error = 2;
	else
		mini->flags->redirect->red_error = 3;
}

void	ft_four_plus(t_mini *mini, char *input)
{
	if (input[0] == input[1])
	{
		if (input[2] == input[3])
			mini->flags->redirect->red_error = 4;
		else
			mini->flags->redirect->red_error = 2;
	}
	else
		mini->flags->redirect->red_error = 3;
}

int	ft_red_count(t_mini *mini)
{
	int	i;

	i = 0;
	i += mini->flags->redirect->do_le;
	i += mini->flags->redirect->do_ri;
	i += mini->flags->redirect->si_le;
	i += mini->flags->redirect->si_ri;
	return (i);
}
