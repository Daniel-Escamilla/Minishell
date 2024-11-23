/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:44:39 by descamil          #+#    #+#             */
/*   Updated: 2024/11/23 11:46:21 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../minishell.h"

// 〖─◇──◇──◇──◇──◇──◇──◇──◇──◇──◇──◇──◇──◇│◇──◇──◇──◇──◇──◇──◇──◇──◇──◇──◇──◇─〗
//                                   〘BUILTINGS〙
// ft_builtin.c
int		ft_exec_built(t_mini *mini, t_cmd *cmd);
char	*ft_builtins(t_cmd *cmd, char *comm);

// ft_cd.c
int		ft_cd(t_mini *mini, t_cmd *cmd);

// ft_change_env.c
void	ft_remove_var(char ***env, int i);
char	*ft_get_var(char **env, char *variable);
void	ft_add_var(char ***env, char *variable, char *content);
void	ft_change_env(char ***env, char *variable, char *content);

// ft_echo.c
int		ft_echo(t_cmd *cmd);

// ft_env.c
int		ft_env(t_mini *mini, t_cmd *cmd);

// ft_exit.c
int		ft_exit(t_mini *mini, t_cmd *cmd);

// ft_export_print
int		ft_print_order(char **env, t_cmd *cmd);

// ft_export.c
int		ft_export(t_mini *mini, t_cmd *cmd);
int		ft_find_var_value(char **env, char *arg);

// ft_pwd.c
int		ft_pwd(t_cmd *cmd);

// ft_unset.c
int		ft_unset(t_mini *mini, t_cmd *cmd);

#endif
