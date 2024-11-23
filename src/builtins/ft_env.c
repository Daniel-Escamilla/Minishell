/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:49:28 by descamil          #+#    #+#             */
/*   Updated: 2024/11/23 18:09:07 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int	ft_env(t_mini *mini, t_cmd *cmd)
{
	int	i;

	i = -1;
	if (ft_strstr_len(cmd->args) > 1)
	{
		write(2, "env: ", 6);
		write(2, cmd->args[1], ft_strlen(cmd->args[1]));
		write(2, " : No such file or directory\n", 29);
		return (127);
	}
	while (mini->env->env && mini->env->env[++i])
	{
		write(cmd->names->fd_outfile, mini->env->env[i],
			ft_strlen(mini->env->env[i]));
		write(cmd->names->fd_outfile, "\n", 1);
	}
	return (0);
}
