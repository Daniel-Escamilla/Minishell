/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 09:32:44 by descamil          #+#    #+#             */
/*   Updated: 2024/11/13 16:46:47 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

char	*ft_create_filename(char **files, int status)
{
	char	*filename;
	char	*number;
	int		index;

	index = 0;
	filename = ft_strdup(".here_doc");
	while (access(filename, F_OK) != -1)
	{
		free(filename);
		number = ft_itoa(index++);
		filename = ft_strjoin(".here_doc", number);
		free(number);
	}
	if (files == NULL && status == 0)
		return (filename);
	while (access(filename, F_OK) != -1 || ft_strnstrstr(files, filename) != 0)
	{
		free(filename);
		number = ft_itoa(index++);
		filename = ft_strjoin(".here_doc", number);
		free(number);
	}
	return (filename);
}

static void	ft_do_here_doc(t_mini *mini, t_cmd *cmd, char **env)
{
	t_cmd	*current;
	int		i;

	current = cmd;
	while (current)
	{
		i = 0;
		while (current->files->order && current->files->order[i])
		{
			if (ft_atoi(current->files->order[i]) == 3)
				ft_write_here_doc(mini, current, env, i);
			i++;
		}
		current = current->next;
	}
}

static void	ft_get_files(char ***files, char *file)
{
	char	**tmp;

	tmp = ft_strstr_dup(*files);
	ft_strstr_free(*files);
	*files = ft_sindub_join(tmp, file);
	ft_strstr_free(tmp);
}

static void	ft_create_files(t_mini *mini, t_cmd *cmd)
{
	t_cmd	*current;
	char	*file;
	int		i;

	current = cmd;
	while (current)
	{
		i = -1;
		while (current->files->order && current->files->order[++i])
		{
			if (ft_atoi(current->files->order[i]) == 3
				&& (current->files->order[i + 1] == NULL))
			{
				file = ft_create_filename(mini->files, 1);
				if (mini->files != NULL)
					ft_get_files(&mini->files, file);
				else
					mini->files = ft_sindub_join(NULL, file);
				free(file);
			}
		}
		current = current->next;
	}
}

int	ft_here_doc(t_mini *mini, t_cmd *cmd, char **env)
{
	pid_t	pid;
	int		status;

	ft_create_files(mini, cmd);
	pid = fork();
	if (pid == -1)
		ft_perror_exit("Error in Fork", 1);
	else if (pid == 0)
	{
		close(mini->fd_history);
		ft_signal_management(0);
		ft_do_here_doc(mini, cmd, env);
		exit(0);
	}
	else
		waitpid(pid, &status, 0);
	if (mini->files != NULL && g_exit_status == 130)
	{
		ft_unlink_hd(mini);
		return (1);
	}
	return (0);
}
