/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:37:57 by smarin-a          #+#    #+#             */
/*   Updated: 2024/09/15 21:43:50 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_many_args_error(int argc, char **argv)
{
    char    *error_msg;
    char    *temp;
    
    if (argc < 2)
        return;
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

// int main(int argc, char **argv)
// {
//     ft_many_args_error(argc, argv);
//     return 0;
// }

// void	ft_many_args_error(char **argv)
// {
// 	size_t	len;

// 	len = ft_strlen(argv[0]);
// 	if (ft_strlen(argv[0]) < ft_strlen(argv[1]))
// 		len = ft_strlen(argv[1]);
// 	if (ft_strncmp(argv[0], argv[1], len) == 0)
// 		ft_put_error(argv[0], argv[1], "Cannot execute binary file");
// 	else
// 		ft_put_error(argv[0], argv[1], "No such file or directory");
// 	printf("\nSALIDA 3\n\n");
// 	exit (127);
// }

void	ft_exit_error(t_mini *mini, char *error_msg, int exit_status)
{
	close (mini->fd_history);
	printf("%s\n", error_msg);
	printf("\nSALIDA 2\n\n");
	free_t_mini(mini);
	exit(exit_status);
}
