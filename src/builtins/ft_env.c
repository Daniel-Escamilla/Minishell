/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarin-a <smarin-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:49:28 by descamil          #+#    #+#             */
/*   Updated: 2025/03/05 11:24:50 by smarin-a         ###   ########.fr       */
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
		if (ft_strncmp(env[i], "_=", 2) == 0)
		{
			write(STDOUT_FILENO, "_=/usr/bin/env\n", 15);
			continue ;
		}
		write(STDOUT_FILENO, env[i], ft_strlen(env[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}
