/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 09:29:06 by descamil          #+#    #+#             */
/*   Updated: 2024/09/11 23:23:24 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_validate_comm(char *cmd, char **path, int j)
{
	char	*command;
	char	*test;

	if (access(cmd, X_OK) == 0 && ft_strrchr(cmd, '/'))
	{
		command = ft_strdup(cmd);
		return (command);
	}
	if (access(cmd, X_OK) != 0 && ft_strrchr(cmd, '/'))
		return (NULL);
	command = ft_strjoin("/", cmd);
	if (path == NULL)
		return (NULL);
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
	{
		printf("Ese comando no existe, prueba otro\n");
		current->files->error = -3;
		ft_strstr_free(path);
		return (NULL);
	}
	ft_strstr_free(path);
	return (cmd);
}

void	ft_comm(t_cmd *cmd, t_mini *mini)
{
	if (mini->num_comm != 0)
	{
		if (pipe(mini->fd_pipe) == -1)
			perror("Pipe Error");
	}
	ft_open_fd(cmd, mini);
	if (cmd->cmd == NULL)
		return ;
	if (cmd->names->fd_infile != -1 && cmd->names->fd_outfile != -1 && cmd->files->error != -3)
	{
		mini->proc[mini->index] = fork();
		if (mini->proc[mini->index] == -1)
			perror("Failed in Fork()");
		if (mini->proc[mini->index] == 0)
		{
			dup2(cmd->names->fd_infile, STDIN_FILENO);
			dup2(cmd->names->fd_outfile, STDOUT_FILENO);
			ft_close_fd(mini, 'H');
			if (cmd->built == 1)
			{
				ft_exec_built(cmd);
				ft_putstr_fd("BUILT\n", 2);
				close(mini->fd_pipe[1]);
				close(mini->fd_history);
				exit(0);
			}
			else
			{
				execve(cmd->cmd, cmd->args, mini->env->env);
				perror("Execve Error");
			}
		}
		ft_close_fd(mini, 'P');
		if (cmd->names->join)
		{
			unlink(cmd->names->join);
			free(cmd->names->join);
		}
	}
	else
	{
		close(mini->fd_pipe[0]);
		close(mini->fd_pipe[1]);
		if (mini->fd_tmp != 0)
			close(mini->fd_tmp);
	}
	mini->index++;
}
