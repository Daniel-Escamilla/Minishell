/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:45:25 by descamil          #+#    #+#             */
/*   Updated: 2024/11/09 20:59:13 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../minishell.h"

// 〖─◇──◇──◇──◇──◇──◇──◇──◇──◇──◇──◇──◇──◇│◇──◇──◇──◇──◇──◇──◇──◇──◇──◇──◇──◇─〗
//                                    〘PARSER〙
// ft_check_input.c
int		ft_error_rqp(t_mini *mini, char *input);
char	**ft_check_input(t_mini *mini, char *input);

// ft_check_operators.c
int		ft_is_not_mayor_n_minor_char(char c);

// ft_check_pipes.c
int		ft_count_pipes(char *input, int amount, int character, int i);

// ft_check_quotes.c
int		ft_locate_next_quote(int i, char *input, char quote);
int		ft_check_quote(char *input, int simp, int doub, t_mini *mini);

// ft_do_comm.c
int		ft_do_comm(t_cmd *cmd, t_mini *mini);
int		ft_order_all(t_mini *mini, t_cmd **cmd, char **lines, char *input);

// ft_lexer.c
void	ft_unlink_hd(t_mini *mini);
void	ft_recive_input(t_mini *mini);

// ft_manage_quotes.c
void	ft_do_remove_quotes(t_cmd *cmd);

// ft_manage_spaces.c
void	ft_quit_spaces(t_cmd **cmd);

// ft_parser.c
int		ft_sizes(t_cmd *current);
void	ft_start_val(t_cmd *cmd);
int		ft_wait_bonus(t_mini *mini);
char	**ft_create_path(char **env);

// ft_quit_quotes.c
int		ft_has_quotes(char *str, int i);
int		*ft_find_quotes(char *str, int i);
void	ft_rm_quotes(char **str, int *quotes);

// ft_split_pipe.c
char	**ft_split_pipe(const char *s, char c);

// ft_strtok.c
int		ft_strtok(t_mini *mini, t_cmd **cmd, char *input);

#endif
