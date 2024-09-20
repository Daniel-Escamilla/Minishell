/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 23:10:06 by user              #+#    #+#             */
/*   Updated: 2024/09/20 23:52:23 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTS_H
# define REDIRECTS_H

# include "../minishell.h"

// ft_redirects.c
int		ft_count_redirect(t_mini *mini, char *input, int i);

// ft_redirects_utils.c
int		ft_red_count(t_mini *mini);
void	ft_one(t_mini *mini, char *input);
void	ft_two(t_mini *mini, char *input);
void	ft_three(t_mini *mini, char *input);
void	ft_four_plus(t_mini *mini, char *input);

// ft_split_red.c
int		is_redirection(char c, char c1);
char	**ft_split_red(const char *input, int i);

#endif
