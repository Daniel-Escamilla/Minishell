/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:34:11 by smarin-a          #+#    #+#             */
/*   Updated: 2024/11/10 17:18:17 by descamil         ###   ########.fr       */
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

static void	ft_here_doc_handler(int signal)
{
	int	dup_fd;
	int	fd;

	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		fd = 2;
		while (++fd < 1024)
		{
			dup_fd = dup(fd);
			if (dup_fd != -1)
			{
				close(fd);
				close(dup_fd);
			}
		}
		exit(130);
	}
	else if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	return;
}

void	ft_signal_management(int i)
{
	struct sigaction	sig_act;

	sigemptyset(&sig_act.sa_mask);
	if (i == 1)
		sig_act.sa_handler = &ft_signal_handler;
	else
		sig_act.sa_handler = &ft_here_doc_handler;
	sig_act.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sig_act, NULL);
	sigaction(SIGQUIT, &sig_act, NULL);
}
