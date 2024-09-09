/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:09:37 by smarin-a          #+#    #+#             */
/*   Updated: 2024/09/09 09:55:02 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	leaks(void)
// {
// 	system("leaks -q minishell");
// }
// atexit(leaks);
int	g_exit_status;

int	main(int argc, char **argv, char **env)
{
	t_mini	*mini;

	if (argc != 1)
		ft_many_args_error(argv);
	mini = ft_initialize(env);
	g_exit_status = 0;
	ft_mini_header();
	ft_signal_management(1);
	ft_recive_input(mini);
	printf("\nSALIDA 1\n\n");
	free_t_cmd(&mini->cmd);
	free_t_mini(mini);
	close(mini->fd_history);
	return (0);
}
