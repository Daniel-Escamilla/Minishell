/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:34:11 by smarin-a          #+#    #+#             */
/*   Updated: 2024/10/13 15:56:33 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/signals.h"

static void	ft_signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 130;
	}
	else if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

static void	ft_child_signal_handler(int signal)
{
	if (signal == SIGINT)
		g_exit_status = 130;
	else if (signal == SIGQUIT)
	{
		printf("Quit: 3\n");
		g_exit_status = 131;
	}
	return ;
}

void	ft_signal_management(int i)
{
	struct sigaction	sig_act;

	sigemptyset(&sig_act.sa_mask);
	if (i)
		sig_act.sa_handler = &ft_signal_handler;
	else
		sig_act.sa_handler = &ft_child_signal_handler;
	sig_act.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sig_act, NULL);
	sigaction(SIGQUIT, &sig_act, NULL);
}
