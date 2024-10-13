/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:53:58 by descamil          #+#    #+#             */
/*   Updated: 2024/10/13 03:51:34 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int	ft_unset(t_mini *mini, t_cmd *cmd)
{
	char	*tmp;
	int		var;
	int		i;

	i = 1;
	while (cmd->args[i])
	{
		tmp = ft_strdup(cmd->args[i]);
		free(cmd->args[i]);
		cmd->args[i] = ft_strjoin(tmp, "=");
		free(tmp);
		i++;
	}
	i = 1;
	while (cmd->args[i])
	{
		var = ft_dup_var(mini, cmd->args[i]);
		if (var != -1)
			ft_remove_var(&mini->env->env, var);
		i++;
	}
	return (0);
}
