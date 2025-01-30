/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:53:58 by descamil          #+#    #+#             */
/*   Updated: 2025/01/30 12:12:18 by descamil         ###   ########.fr       */
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
		if (ft_strnstr(cmd->args[i], "_", 1))
			i++;
		if (cmd->args[i] == NULL)
			return (0);
		if (ft_strnstr(cmd->args[i], "PWD", 3))
			mini->pwd = 1;
		if (ft_strnstr(cmd->args[i], "OLDPWD", 6))
			mini->oldpwd = 1;
		if (ft_strnstr(cmd->args[i], "PATH", 4))
			mini->path = 1;
		tmp = ft_strjoin(cmd->args[i], "=");
		var = ft_find_var_value(mini->env->env, tmp);
		if (var != -1)
			ft_remove_var(&mini->env->env, var);
		free(tmp);
		i++;
	}
	return (0);
}
