/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 22:58:52 by user              #+#    #+#             */
/*   Updated: 2024/09/20 23:52:20 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../minishell.h"

// ft_check_input.c
char	**ft_check_input(t_mini *mini, char *input);

// ft_check_operators.c
int		ft_is_not_mayor_n_minor_char(char c);

// ft_check_pipes.c
int		ft_count_pipes(char *input, int amount, int character);

// ft_check_quotes.c
int		ft_locate_next_quote(int i, char *input, char quote);
int		ft_check_quote(char *input, int simp, int doub, t_mini *mini);

// ft_lexer.c
void	ft_recive_input(t_mini *mini);

// ft_parser.c
int		ft_sizes(t_cmd *current);
void	ft_start_val(t_cmd *cmd);
int		ft_wait_bonus(t_mini *mini);
char	**ft_create_path(char **env);

// ft_split_pipe.c
char	**ft_split_pipe(const char *s, char c);

// ft_strtok.c
int		ft_strtok(t_mini *mini, t_cmd **cmd, char *input);

#endif
