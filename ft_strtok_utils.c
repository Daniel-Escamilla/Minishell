/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:31:15 by descamil          #+#    #+#             */
/*   Updated: 2024/09/17 16:33:16 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_minus_one(t_mini *mini)
{
	if (mini->flags->pipe == -1 || mini->flags->quote == -1
		|| mini->flags->locate_red == -1)
		return (-1);
	return (0);
}

void	ft_start_comm_val(t_mini **mini)
{
	(*mini)->index = 0;
	(*mini)->fd_tmp = 0;
	(*mini)->num_comm = (*mini)->flags->pipe + 1;
	(*mini)->proc = ft_calloc(sizeof(pid_t), (*mini)->num_comm + 1);
}
