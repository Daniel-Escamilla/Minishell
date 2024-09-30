/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:05:39 by user              #+#    #+#             */
/*   Updated: 2024/09/30 12:08:16 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../minishell.h"

// ft_builtin.c
int		ft_exec_built(t_cmd *cmd);
char	*ft_builtins(t_cmd *cmd, char *comm);

// ft_cd.c
int		ft_cd(t_cmd *cmd);

// ft_change_env.c
void	ft_change_env(char ***env, char *variable, char *content);

#endif
