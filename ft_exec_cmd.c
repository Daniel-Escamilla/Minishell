/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 09:29:06 by descamil          #+#    #+#             */
/*   Updated: 2024/09/03 09:31:46 by descamil         ###   ########.fr       */
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
		current->error = -2;
		return (NULL);
	}
	if (path == NULL)
		path = ft_save_path(mini->env->env);
	cmd = ft_validate_comm(tmp, path, 1);
	if (cmd == NULL)
	{
		printf("Ese comando no existe, prueba otro\n");
		mini->error = -2;
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
	if (cmd->names->fd_infile != -1 && cmd->names->fd_outfile != -1)
	{
		mini->proc[mini->index] = fork();
		if (mini->proc[mini->index] == -1)
			perror("Failed in Fork()");
		if (mini->proc[mini->index] == 0)
		{
			dup2(cmd->names->fd_infile, STDIN_FILENO);
			dup2(cmd->names->fd_outfile, STDOUT_FILENO);
			ft_close_fd(mini, 'H');
			if (ft_strnstr(cmd->cmd, "/usr/bin/env", ft_strlen("/usr/bin/env")) != NULL)
				ft_strstr_printf(mini->env->env);
			else
			{
				execve(cmd->cmd, cmd->args, mini->env->env);
				perror("Execve Error");
			}
		}
		ft_close_fd(mini, 'P');
		if (cmd->names->fd_infile != 0 && cmd->names->fd_infile != mini->fd_pipe[0])
			close(cmd->names->fd_infile);
		if (cmd->names->fd_outfile != 1 && cmd->names->fd_outfile != mini->fd_pipe[1])
			close(cmd->names->fd_outfile);
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
