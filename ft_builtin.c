/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:09:02 by user              #+#    #+#             */
/*   Updated: 2024/09/09 10:54:28 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void    ft_env(t_mini *mini)
// {
// 
// }

// int	ft_cd(t_mini *mini, t_cmd *cmd)
// {
// 	if (chdir(cmd->cmd) == 0)
// 	;
// }

int	ft_exec_built(t_mini *mini, t_cmd *cmd)
{
	int	exit;
	
	exit = 0;
	if (ft_strncmp(cmd->cmd, "cd", 2) == 0 && ft_strlen(cmd->cmd) == 2)
		// exit = ft_cd(mini, cmd);
		exit = 1;
	if (ft_strncmp(cmd->cmd, "pwd", 3) == 0 && ft_strlen(cmd->cmd) == 3)
		exit = 2;
	if (ft_strncmp(cmd->cmd, "env", 3) == 0 && ft_strlen(cmd->cmd) == 3)
		exit = 3;
	if (ft_strncmp(cmd->cmd, "echo", 4) == 0 && ft_strlen(cmd->cmd) == 4)	
		exit = 4;
	if (ft_strncmp(cmd->cmd, "exit", 4) == 0 && ft_strlen(cmd->cmd) == 4)
		exit = 5;
	if (ft_strncmp(cmd->cmd, "unset", 5) == 0 && ft_strlen(cmd->cmd) == 5)
		exit = 6;
	if (ft_strncmp(cmd->cmd, "export", 6) == 0 && ft_strlen(cmd->cmd) == 6)
		exit = 7;
	if (exit == 0)
		mini->error = -2;
	return (exit);
}

char	*ft_builtins(t_cmd *cmd, char *comm)
{
	char	*str;
	
	str = NULL;
	if (ft_strncmp(comm, "cd", 2) == 0 && ft_strlen(comm) == 2)
		str = ft_strdup(comm);
	if (ft_strncmp(comm, "pwd", 3) == 0 && ft_strlen(comm) == 3)
		str = ft_strdup(comm);
	if (ft_strncmp(comm, "env", 3) == 0 && ft_strlen(comm) == 3)
		str = ft_strdup(comm);
	if (ft_strncmp(comm, "echo", 4) == 0 && ft_strlen(comm) == 4)	
		str = ft_strdup(comm);
	if (ft_strncmp(comm, "exit", 4) == 0 && ft_strlen(comm) == 4)
		str = ft_strdup(comm);
	if (ft_strncmp(comm, "unset", 5) == 0 && ft_strlen(comm) == 5)
		str = ft_strdup(comm);
	if (ft_strncmp(comm, "export", 6) == 0 && ft_strlen(comm) == 6)	
		str = ft_strdup(comm);
	if (str != NULL)
		cmd->built = 1;
	return(str);
}
