/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:09:37 by smarin-a          #+#    #+#             */
/*   Updated: 2024/10/24 11:50:44 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

int	g_exit_status;

int	main(int argc, char **argv, char **env)
{
	t_mini	*mini;

	ft_many_args_error(argc, argv);
	mini = ft_initialize(env);
	ft_mini_header();
	ft_signal_management(1);
	ft_recive_input(mini);
	printf("\nSALIDA 1\n\n");
	free_t_cmd(&mini->cmd);
	if (mini->fd_history != -1)
		close(mini->fd_history);
	free_t_mini(mini);
	return (0);
}
