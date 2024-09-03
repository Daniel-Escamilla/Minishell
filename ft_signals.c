/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:34:11 by smarin-a          #+#    #+#             */
/*   Updated: 2024/09/03 17:06:23 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 1;
	}
	else if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}
// Manejo de señales en el proceso principal: SIGINT borra la línea de entrada y SIGQUIT solo redisplay.

void	ft_child_signal_handler(int signal)
{
	if (signal == SIGINT)
		g_exit_status = 130;
	else if (signal == SIGQUIT)
	{
		write(1, "Quit: 3\n", 9);
		g_exit_status = 131;
	}
	return ;
}
// Manejo de señales en procesos hijos: SIGINT establece el estado de salida a 130 y SIGQUIT imprime mensaje y establece el estado a 131.

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
