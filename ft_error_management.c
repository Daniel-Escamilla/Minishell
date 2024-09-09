/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:37:57 by smarin-a          #+#    #+#             */
/*   Updated: 2024/09/03 12:59:33 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_put_error(char *bash, char *file, char *error_msg)
{
	ft_putstr_fd(bash, 2);
	ft_putstr_fd(": ", 2);
	if (file) // BORRAR FUNC
	{
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": ", 2);
	}
	if (error_msg)
		ft_putendl_fd(error_msg, 2);
}

void	ft_many_args_error(char **argv)
{
	size_t	len;

	len = ft_strlen(argv[0]);
	if (ft_strlen(argv[0]) < ft_strlen(argv[1]))
		len = ft_strlen(argv[1]);
	if (ft_strncmp(argv[0], argv[1], len) == 0)
		ft_put_error(argv[0], argv[1], "Cannot execute binary file");
	else
		ft_put_error(argv[0], argv[1], "No such file or directory");
	printf("\nSALIDA 3\n\n");
	exit (127);
}

void	ft_exit_error(t_mini *mini, char *error_msg, int exit_status)
{
	close (mini->fd_history);
	printf("%s\n", error_msg);
	printf("\nSALIDA 2\n\n");
	// free_t_cmd(&(mini->cmd));
	free_t_mini(mini);
	exit(exit_status);
}
