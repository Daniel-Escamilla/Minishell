/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:45:56 by descamil          #+#    #+#             */
/*   Updated: 2024/11/10 20:48:47 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../minishell.h"

// 〖─◇──◇──◇──◇──◇──◇──◇──◇──◇──◇──◇──◇──◇│◇──◇──◇──◇──◇──◇──◇──◇──◇──◇──◇──◇─〗
//                                     〘UTILS〙
// ft_free.c
void	free_t_cmd(t_cmd **cmd);
void	free_t_mini(t_mini *mini);

// ft_str_utils.c
int		ft_strstr_len(char **str);
void	ft_strstr_free(char **str);
char	**ft_strstr_dup(char **str);
int		ft_strnstrstr(char **str, char *locate);
char	**ft_strstr_join(char **str, char **str1);

// ft_str_utils2.c
int		ft_strlen_dup(char *argv);
char	**ft_sindub_join(char **str, char *str1);
char	*ft_strchr_mod(char *str, int value, int stop);
void	ft_three_arguments_printf(char *prefix, char *arg, char *suffix);

// ft_utils.c
int		ft_history(void);
void	safe_close(int *fd);
void	ft_mini_header(void);
void	ft_strstr_printf(char **str);

//ft_utils2.c
void	ft_perror_exit(char *error, int exit);
void	ft_printf_exit(char *error, char *arguments, int exit);

#endif
