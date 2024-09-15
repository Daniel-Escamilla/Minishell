/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 09:29:06 by descamil          #+#    #+#             */
/*   Updated: 2024/09/15 21:10:50 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_validate_comm_part1(char *cmd)
{
	char	*command;

	if (access(cmd, X_OK) == 0 && ft_strrchr(cmd, '/'))
	{
		command = ft_strdup(cmd);
		return (command);
	}
	if (access(cmd, X_OK) != 0 && ft_strrchr(cmd, '/'))
		return (NULL);
	command = ft_strjoin("/", cmd);
	return (command);
}

char	*ft_validate_comm_part2(char **path, int j, char *command)
{
	char	*test;

	while (path[j] != NULL)
	{
		test = ft_strjoin(path[j++], command);
		if (access(test, X_OK) == 0)
		{
			free(command);
			return (test);
		}
		free(test);
	}
	free(command);
	return (NULL);
}

char	*ft_validate_comm(char *cmd, char **path, int j)
{
	char	*command;

	command = ft_validate_comm_part1(cmd);
	if (command == NULL || ft_strrchr(cmd, '/'))
		return (command);
	if (path == NULL)
	{
		free(command);
		return (NULL);
	}
	return (ft_validate_comm_part2(path, j, command));
}

char	*ft_route_cmd(t_mini *mini, t_cmd *current, char *tmp)
{
	char	**path;
	char	*cmd;

	path = ft_create_path(mini->env->env);
	if (tmp[0] == '\0')
	{
		ft_strstr_free(path);
		current->files->error = -2;
		return (NULL);
	}
	if (path == NULL)
		path = ft_save_path(mini->env->env);
	cmd = ft_validate_comm(tmp, path, 1);
	if (cmd == NULL)
		current->files->error = -3;
	ft_strstr_free(path);
	return (cmd);
}
