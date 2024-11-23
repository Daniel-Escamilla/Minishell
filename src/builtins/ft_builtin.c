/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:09:02 by user              #+#    #+#             */
/*   Updated: 2024/11/23 11:34:38 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int	ft_exec_built(t_mini *mini, t_cmd *cmd)
{
	int	exit;

	exit = 0;
	if (ft_strncmp(cmd->cmd, "cd", 2) == 0 && ft_strlen(cmd->cmd) == 2)
		exit = ft_cd(mini, cmd);
	if (ft_strncmp(cmd->cmd, "pwd", 3) == 0 && ft_strlen(cmd->cmd) == 3)
		exit = ft_pwd(cmd);
	if (ft_strncmp(cmd->cmd, "env", 3) == 0 && ft_strlen(cmd->cmd) == 3)
		exit = ft_env(mini, cmd);
	if (ft_strncmp(cmd->cmd, "echo", 4) == 0 && ft_strlen(cmd->cmd) == 4)
		exit = ft_echo(cmd);
	if (ft_strncmp(cmd->cmd, "exit", 4) == 0 && ft_strlen(cmd->cmd) == 4)
		exit = ft_exit(mini, cmd);
	if (ft_strncmp(cmd->cmd, "unset", 5) == 0 && ft_strlen(cmd->cmd) == 5)
		exit = ft_unset(mini, cmd);
	if (ft_strncmp(cmd->cmd, "export", 6) == 0 && ft_strlen(cmd->cmd) == 6)
		exit = ft_export(mini, cmd);
	return (exit);
}

char	*ft_builtins(t_cmd *cmd, char *comm)
{
	size_t		i;
	char		*str;
	const char	*builtins[] = {"cd", "pwd", "env", "echo",
		"exit", "unset", "export", NULL};

	i = 0;
	str = NULL;
	while (i < 7)
	{
		if (ft_strncmp(comm, builtins[i], ft_strlen(builtins[i])) == 0
			&& ft_strlen(comm) == ft_strlen(builtins[i]))
		{
			str = ft_strdup(comm);
			cmd->built = 1;
			break ;
		}
		i++;
	}
	return (str);
}
