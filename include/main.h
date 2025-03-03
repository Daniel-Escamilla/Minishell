/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:45:17 by descamil          #+#    #+#             */
/*   Updated: 2025/03/03 19:41:11 by descamil         ###   ########.fr       */
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

// ft_update_env.c
char	**ft_upgrade_env(char **str, size_t i);

#endif
