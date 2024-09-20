/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:56:04 by descamil          #+#    #+#             */
/*   Updated: 2024/09/20 23:20:58 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static char	*ft_father(int *fd, char **args)
{
	char	*line;

	ft_strstr_free(args);
	close(fd[1]);
	line = get_next_line(fd[0]);
	while (line != NULL)
	{
		if (ft_strnstr(line, "search-binaries-default:",
				ft_strlen("search-binaries-default:")) != NULL)
		{
			close(fd[0]);
			return (line);
		}
		free(line);
		line = get_next_line(fd[0]);
	}
	return (NULL);
}

static void	ft_pid_0(int *fd, char *path, char **args, char **env)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	execve(path, args, env);
	ft_strstr_free(args);
	free(path);
	perror("execve");
	exit(1);
}

static char	*ft_execute(char **env)
{
	char	**args;
	char	*path;
	char	*line;
	int		fd[2];
	pid_t	pid;

	path = ft_strdup("/usr/bin/systemd-path");
	args = (char **)ft_calloc(sizeof(char *), 2);
	if (args == NULL)
		return (NULL);
	args[0] = ft_strdup("systemd-path");
	if (access("/usr/bin/systemd-path", X_OK) == -1)
		return (NULL);
	if (pipe(fd) == -1)
		return (NULL);
	pid = fork();
	if (pid == -1)
		return (NULL);
	if (pid == 0)
		ft_pid_0(fd, path, args, env);
	else
		line = ft_father(fd, args);
	free(path);
	return (line);
}

char	**ft_save_path(char	**env)
{
	char	**path;
	char	*line;
	char	*trim;

	line = ft_execute(env);
	trim = ft_strtrim(line, "\n");
	free(line);
	path = ft_split(trim + ft_strlen("search-binaries-default: "), ':');
	free(trim);
	return (path);
}
