/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:49:28 by descamil          #+#    #+#             */
/*   Updated: 2025/01/16 18:21:18 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int	ft_env(t_mini *mini, t_cmd *cmd)
{
	int	i;

	i = -1;
	if (ft_strstr_len(cmd->args) > 1)
	{
		write(1, "env: ", 6);
		write(1, cmd->args[1], ft_strlen(cmd->args[1]));
		write(1, " : No such file or directory\n", 29);
		return (127);
	}
	while (mini->env->env && mini->env->env[++i])
		printf("%s\n", mini->env->env[i]);
	return (0);
}
