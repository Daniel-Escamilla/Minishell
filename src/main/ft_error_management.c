/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:37:57 by smarin-a          #+#    #+#             */
/*   Updated: 2024/09/21 12:27:27 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	ft_many_args_error(int argc, char **argv)
{
	char	*error_msg;
	char	*temp;

	if (argc < 2)
		return ;
	temp = ft_strjoin("mini: ", argv[1]);
	if (!temp)
	{
		perror("Error al asignar memoria");
		exit(1);
	}
	error_msg = ft_strjoin(temp, ": No such file or directory");
	free(temp);
	if (!error_msg)
	{
		perror("Error al asignar memoria");
		exit(1);
	}
	printf("%s\n", error_msg);
	free(error_msg);
	exit(127);
}

void	ft_exit_error(t_mini *mini, char *error_msg, int exit_status)
{
	close (mini->fd_history);
	mini->fd_history = -1;
	printf("%s\n", error_msg);
	printf("\nSALIDA 2\n\n");
	free_t_mini(mini);
	exit(exit_status);
}
// Salida para exit antiguo
