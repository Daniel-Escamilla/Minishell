/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 09:29:06 by descamil          #+#    #+#             */
/*   Updated: 2024/09/12 20:52:15 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*ft_validate_comm(char *cmd, char **path, int j)
// {
// 	char	*command;
// 	char	*test;

// 	if (access(cmd, X_OK) == 0 && ft_strrchr(cmd, '/'))
// 	{
// 		command = ft_strdup(cmd);
// 		return (command);
// 	}
// 	if (access(cmd, X_OK) != 0 && ft_strrchr(cmd, '/'))
// 		return (NULL);
// 	command = ft_strjoin("/", cmd);
// 	if (path == NULL)
// 		return (NULL);
// 	while (path[j] != NULL)
// 	{
// 		test = ft_strjoin(path[j++], command);
// 		if (access(test, X_OK) == 0)
// 		{
// 			free(command);
// 			return (test);
// 		}
// 		free(test);
// 	}
// 	free(command);
// 	return (NULL);
// }

// char	*ft_route_cmd(t_mini *mini, t_cmd *current, char *tmp)
// {
// 	char	**path;
// 	char	*cmd;

// 	path = ft_create_path(mini->env->env);
// 	if (tmp[0] == '\0')
// 	{
// 		ft_strstr_free(path);
// 		current->files->error = -2;
// 		return (NULL);
// 	}
// 	if (path == NULL)
// 		path = ft_save_path(mini->env->env);
// 	cmd = ft_validate_comm(tmp, path, 1);
// 	if (cmd == NULL)
// 	{
// 		current->files->error = -3;
// 		ft_strstr_free(path);
// 		return (NULL);
// 	}
// 	ft_strstr_free(path);
// 	return (cmd);
// }

// void	ft_comm(t_cmd *cmd, t_mini *mini)
// {
// 	if (mini->num_comm != 0)
// 	{
// 		if (pipe(mini->fd_pipe) == -1)
// 			perror("Pipe Error");
// 	}
// 	ft_open_fd(cmd, mini);
// 	if (cmd->cmd == NULL)
// 		printf("%s: command not found\n", cmd->args[0]);
// 	if (cmd->names->fd_infile != -1 && cmd->names->fd_outfile != -1 && cmd->files->error != -3)
// 	{
// 		mini->proc[mini->index] = fork();
// 		if (mini->proc[mini->index] == -1)
// 			perror("Failed in Fork()");
// 		if (mini->proc[mini->index] == 0)
// 		{
// 			dup2(cmd->names->fd_infile, STDIN_FILENO);
// 			dup2(cmd->names->fd_outfile, STDOUT_FILENO);
// 			ft_close_fd(mini, 'H');
// 			if (cmd->built == 1)
// 			{
// 				ft_exec_built(cmd);
// 				ft_putstr_fd("BUILT\n", 2);
// 				close(mini->fd_pipe[1]);
// 				close(mini->fd_history);
// 				exit(0);
// 			}
// 			else
// 			{
// 				execve(cmd->cmd, cmd->args, mini->env->env);
// 				perror("Execve Error");
// 			}
// 		}
// 		if (cmd->names->fd_infile != 0)
// 			close(cmd->names->fd_infile);
// 		if (cmd->names->fd_outfile != 1)
// 			close(cmd->names->fd_outfile);
// 		ft_close_fd(mini, 'P');
// 	}
// 	else
// 	{
// 		close(mini->fd_pipe[0]);
// 		close(mini->fd_pipe[1]);
// 		if (mini->fd_tmp != 0)
// 			close(mini->fd_tmp);
// 	}
// 	if (cmd->names->join)
// 	{
// 		unlink(cmd->names->join);
// 		free(cmd->names->join);
// 	}
// 	mini->index++;
// }

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

void	ft_comm_part1(t_cmd *cmd, t_mini *mini)
{
	if (mini->num_comm != 0)
	{
		if (pipe(mini->fd_pipe) == -1)
			perror("Pipe Error");
	}
	ft_open_fd(cmd, mini);
	if (cmd->cmd == NULL)
		printf("%s: command not found\n", cmd->args[0]);
}

void	ft_comm_part2(t_cmd *cmd, t_mini *mini)
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

void	ft_comm_part3(t_cmd *cmd, t_mini *mini)
{
	if (cmd->names->fd_infile != STDIN_FILENO && cmd->names->fd_infile > 0)
	{
		close(cmd->names->fd_infile);
		cmd->names->fd_infile = -1;
	}
	if (cmd->names->fd_outfile != STDOUT_FILENO && cmd->names->fd_outfile > 1)
	{
		close(cmd->names->fd_outfile);
		cmd->names->fd_outfile = -1;
	}
	ft_close_fd(mini, 'P');
}

void	ft_comm(t_cmd *cmd, t_mini *mini)
{
	ft_comm_part1(cmd, mini);
	if (cmd->names->fd_infile != -1 && cmd->names->fd_outfile != -1 && cmd->files->error != -3)
	{
		mini->proc[mini->index] = fork();
		if (mini->proc[mini->index] == -1)
			perror("Failed in Fork()");
		if (mini->proc[mini->index] == 0)
			ft_comm_part2(cmd, mini);
		ft_comm_part3(cmd, mini);
	}
	else
	{
		close(mini->fd_pipe[0]);
		close(mini->fd_pipe[1]);
		if (mini->fd_tmp != 0)
			close(mini->fd_tmp);
	}
	if (cmd->names->join)
	{
		unlink(cmd->names->join);
		free(cmd->names->join);
	}
	mini->index++;
}

