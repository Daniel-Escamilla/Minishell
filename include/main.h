/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:45:17 by descamil          #+#    #+#             */
/*   Updated: 2024/10/18 16:04:27 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "../minishell.h"

// 〖─◇──◇──◇──◇──◇──◇──◇──◇──◇──◇──◇──◇──◇│◇──◇──◇──◇──◇──◇──◇──◇──◇──◇──◇──◇─〗
//                                     〘MAIN〙
// ft_error_management.c
void	ft_many_args_error(int argc, char **argv);

// ft_initialize.c
t_mini	*ft_initialize(char **env);

// ft_main.c
int		main(int argc, char **argv, char **env);

#endif
