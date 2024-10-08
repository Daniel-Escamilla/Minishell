/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:44:39 by descamil          #+#    #+#             */
/*   Updated: 2024/10/06 19:39:35 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../minishell.h"

// ft_builtin.c
int		ft_exec_built(t_mini *mini, t_cmd *cmd);
char	*ft_builtins(t_cmd *cmd, char *comm);

// ft_cd.c
int		ft_cd(t_mini *mini, t_cmd *cmd);

// ft_change_env.c
char	*ft_get_var(char **env, char *variable);
void	ft_add_var(char ***env, char *variable, char *content);
void	ft_change_env(char ***env, char *variable, char *content);

// ft_echo.c


// ft_env.c
int		ft_env(t_mini *mini);

// ft_exit.c


// ft_export.c
int		ft_export(t_mini *mini, t_cmd *cmd);

// ft_pwd.c
int		ft_pwd(void);

// ft_unset.c


#endif
