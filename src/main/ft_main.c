/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:09:37 by smarin-a          #+#    #+#             */
/*   Updated: 2024/11/23 16:21:58 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

int	g_exit_status;

int	main(int argc, char **argv, char **env)
{
	t_mini	*mini;
	int		dup_fd;

	ft_many_args_error(argc, argv);
	mini = ft_initialize(env);
	if (mini->tty == 0)
		ft_mini_header();
	ft_signal_management(1);
	ft_recive_input(mini);
	free_t_cmd(&mini->cmd);
	dup_fd = dup(mini->fd_history);
	if (dup_fd != -1)
	{
		close(dup_fd);
		close(mini->fd_history);
	}
	free_t_mini(mini);
	return (0);
}
