/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:45:17 by descamil          #+#    #+#             */
/*   Updated: 2024/10/05 12:45:19 by descamil         ###   ########.fr       */
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
