/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 22:39:30 by user              #+#    #+#             */
/*   Updated: 2024/09/20 23:52:14 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILES_H
# define FILES_H

# include "../minishell.h"

// ft_files.c
void	ft_files(t_cmd *cmd, t_mini *mini, t_files *files);

// ft_files_utils.c
void	ft_select_files(t_cmd *cmd, int i);
void	ft_move_files(t_cmd *cmd, t_mini *mini);
void	ft_remove_files(t_cmd *cmd, t_mini *mini);
void	process_lines(t_cmd **cmd, t_mini *mini, char **lines, int i);

// ft_final_values.c
int		ft_type(char *argv);
int		ft_num_files(t_cmd *cmd);
char	**ft_order(t_cmd *cmd, t_mini *mini);

#endif
