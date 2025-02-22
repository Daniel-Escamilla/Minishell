/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:49:28 by descamil          #+#    #+#             */
/*   Updated: 2025/02/22 11:44:30 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int	ft_env(char **env, t_cmd *cmd)
{
	int	i;

	i = -1;
	if (ft_strstr_len(cmd->args) > 1)
	{
		write(2, "env: ‘", 9);
		write(2, cmd->args[1], ft_strlen(cmd->args[1]));
		write(2, "’: No such file or directory\n", 32);
		return (127);
	}
	while (env && env[++i])
	{
		write(STDOUT_FILENO, env[i], ft_strlen(env[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}
