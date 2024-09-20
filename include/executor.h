/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 22:48:19 by user              #+#    #+#             */
/*   Updated: 2024/09/20 23:52:05 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_h

# include "../minishell.h"

// ft_commands.c
int		is_red(char *argv);
int		ft_count_args(char *input);
t_cmd	*ft_last_command(t_cmd **cmd);
t_cmd	*ft_add_command(char *input, int i);
void	ft_get_args(char *input, int argc, char ***args);

// ft_commands_utils.c
int		ft_nothing(char *input, int i);
int		ft_nothing_r(char *input, int i);
int		ft_find_char(char *input, int i);
void	ft_plus_one(int value1, int value2);
int		ft_process_quotes(char *input, int *i, int *first);

// ft_comm_exec.c
void	ft_comm(t_cmd *cmd, t_mini *mini);
void	ft_comm_part1(t_cmd *cmd, t_mini *mini);
void	ft_comm_part2(t_cmd *cmd, t_mini *mini);

// ft_exec_cmd.c
char	*ft_validate_comm_part1(char *cmd);
char	*ft_validate_comm(char *cmd, char **path, int j);
char	*ft_route_cmd(t_mini *mini, t_cmd *current, char *tmp);
char	*ft_validate_comm_part2(char **path, int j, char *command);

// ft_fds_infile.c
int		ft_more(t_cmd *cmd, int i, int type);
int		ft_pick_infile(t_cmd *cmd, t_mini *mini);

// ft_fds_outfile.c
int		ft_pick_outfile(t_cmd *cmd, t_mini *mini);
int		ft_handle_trunc(t_cmd *cmd, t_mini *mini, int i);
int		ft_handle_append(t_cmd *cmd, t_mini *mini, int i);

// ft_here_doc.c
int		ft_here_doc(t_cmd *cmd, int last, int i);

// ft_manage_fd.c
void	ft_open_fd(t_cmd *cmd, t_mini *mini);
int		ft_choose_infile(t_cmd *cmd, t_mini *mini);
int		ft_choose_outfile(t_cmd *cmd, t_mini *mini);
void	ft_close_and_update_fds(t_mini *mini, char who);

// ft_select_cmd.c
void	ft_select_cmd(t_cmd *current, t_mini *mini, int j);

// ft_commands.c
t_cmd	*ft_add_command(char *input, int i);

// ft_commands_utils.c
int		ft_nothing(char *input, int i);
int		ft_nothing_r(char *input, int i);
void	ft_plus_one(int value1, int value2);

// ft_comm_exec.c
void	ft_comm(t_cmd *cmd, t_mini *mini);

// ft_exec_cmd.c
char	*ft_validate_comm_part1(char *cmd);
char	*ft_validate_comm(char *cmd, char **path, int j);
char	*ft_route_cmd(t_mini *mini, t_cmd *current, char *tmp);
char	*ft_validate_comm_part2(char **path, int j, char *command);

// ft_fds_infile.c
int		ft_more(t_cmd *cmd, int i, int type);
int		ft_pick_infile(t_cmd *cmd, t_mini *mini);

// ft_fds_outfile.c
int		ft_pick_outfile(t_cmd *cmd, t_mini *mini);
int		ft_handle_trunc(t_cmd *cmd, t_mini *mini, int i);
int		ft_handle_append(t_cmd *cmd, t_mini *mini, int i);

// ft_new_args.c
void    ft_new_args(t_cmd *current, int *i);

// ft_here_doc.c
int		ft_here_doc(t_cmd *cmd, int last, int i);

// ft_manage_fd.c
void	ft_open_fd(t_cmd *cmd, t_mini *mini);
void	ft_close_and_update_fds(t_mini *mini, char who);

// ft_get_args_utils.c
int     *ft_sizes_input(char *input, int argc);
char    *ft_inside_argv(char *input, int *size, int stop);
void    ft_free_args(char **argv, int *size, char ***args);

// ft_save_path.c
char	**ft_save_path(char	**env);

// ft_select_cmd.c
void	ft_select_cmd(t_cmd *current, t_mini *mini, int j);

#endif
