/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 22:43:39 by user              #+#    #+#             */
/*   Updated: 2024/09/20 23:51:52 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "../minishell.h"

// ft_error_management.c
void	ft_many_args_error(int argc, char **argv);
void	ft_exit_error(t_mini *mini, char *error_msg, int exit_status);

// ft_initialize.c
t_mini	*ft_initialize(char **env);

// ft_main.c
int		main(int argc, char **argv, char **env);

#endif
