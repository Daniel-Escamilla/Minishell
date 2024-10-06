/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:09:02 by user              #+#    #+#             */
/*   Updated: 2024/10/05 14:02:58 by descamil         ###   ########.fr       */
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
		exit = ft_pwd();
	if (ft_strncmp(cmd->cmd, "env", 3) == 0 && ft_strlen(cmd->cmd) == 3)
		exit = ft_env(mini);
	if (ft_strncmp(cmd->cmd, "echo", 4) == 0 && ft_strlen(cmd->cmd) == 4)
		exit = 4;
	if (ft_strncmp(cmd->cmd, "exit", 4) == 0 && ft_strlen(cmd->cmd) == 4)
		exit = 5;
	if (ft_strncmp(cmd->cmd, "unset", 5) == 0 && ft_strlen(cmd->cmd) == 5)
		exit = 6;
	if (ft_strncmp(cmd->cmd, "export", 6) == 0 && ft_strlen(cmd->cmd) == 6)
		ft_export(mini, cmd);
	return (exit);
}

char	*ft_builtins(t_cmd *cmd, char *comm)
{
	size_t		i;
	char		*str;
	const char	*builtins[] = {"cd", "pwd", "env", "echo",
		"exit", "unset", "export"};

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
