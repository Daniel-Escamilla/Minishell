/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:09:02 by user              #+#    #+#             */
/*   Updated: 2024/09/03 17:50:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void    ft_env(t_mini *mini)
// {
// 	;
// }

void	ft_exec_built(t_mini *mini,t_cmd *cmd)
{
	if (ft_strncmp(cmd->cmd, "cd", 2) == 0 && ft_strlen(cmd->cmd) == 2)
		ft_cd()
	if (ft_strncmp(cmd->cmd, "pwd", 3) == 0 && ft_strlen(cmd->cmd) == 3)
		
	if (ft_strncmp(cmd->cmd, "env", 3) == 0 && ft_strlen(cmd->cmd) == 3)
		
	if (ft_strncmp(cmd->cmd, "echo", 4) == 0 && ft_strlen(cmd->cmd) == 4)	
		
	if (ft_strncmp(cmd->cmd, "exit", 4) == 0 && ft_strlen(cmd->cmd) == 4)
		
	if (ft_strncmp(cmd->cmd, "unset", 5) == 0 && ft_strlen(cmd->cmd) == 5)
		
	if (ft_strncmp(cmd->cmd, "export", 6) == 0 && ft_strlen(cmd->cmd) == 6)	
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
