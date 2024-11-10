/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:44:54 by descamil          #+#    #+#             */
/*   Updated: 2024/11/10 17:31:23 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "../minishell.h"

// 〖─◇──◇──◇──◇──◇──◇──◇──◇──◇──◇──◇──◇──◇│◇──◇──◇──◇──◇──◇──◇──◇──◇──◇──◇──◇─〗
//                                   〘EXPANDER〙
// ft_change_var.c
char	*ft_change_var(char *div, char **env, int i);

// ft_do_expander.c
void	ft_do_expander(t_mini *mini, t_cmd *cmd);

// ft_expand_div.c
char	*expand_div(int *iter, char *str, char **env, int *stop);

// ft_expander.c
char	*ft_expander(char **env, char *str);

// ft_expander_utils1.c
int		ft_size_var(char *str);
char	*ft_dolar_to_iqual(char *div);
char	*ft_join(char **div, char *tmp);

// ft_expander_utils2.c
char	*ft_free_null(char *str);
void	ft_ex_free(char **div, char *tmp);
char	*ft_no_more_dolar(char *div, char *str);

// ft_tript.c
char	**ft_tript(char *str, int size, int start);

#endif
