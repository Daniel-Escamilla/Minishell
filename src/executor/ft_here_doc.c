/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 09:32:44 by descamil          #+#    #+#             */
/*   Updated: 2024/11/10 17:02:29 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

static char	*ft_create_filename(char **files, int status)
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

void	ft_write_fd(char **env, char *eof, int fd, int quotes)
{
	char	*line;
	char	*tmp;
	int		j;

	j = 0;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			printf("mini: warning: here-document at line %d delimited by"
				"end-of-file (wanted `%s')\n", j, eof);
			break ;
		}
		if (ft_strnstr(line, eof, ft_strlen(line))
			&& ft_strlen(eof) == ft_strlen(line))
		{
			free(line);
			break ;
		}
		if (quotes == 0)
		{
			tmp = ft_strdup(line);
			free(line);
			line = ft_expander(env, tmp);
			free(tmp);
		}
		if (write(fd, line, ft_strlen(line)) == -1
			|| write(fd, "\n", 1) == -1)
			printf("Error write");
		free(line);
		j++;
	}
}

void	ft_do_here_doc(t_mini *mini, t_cmd *cmd, char **env)
{
	t_cmd	*current;
	int		*locate;
	char	*file;
	int		quotes;
	int		i;
	int		fd;

	current = cmd;
	while (current)
	{
		i = 0;
		while (current->files->order && current->files->order[i])
		{
			if (ft_atoi(current->files->order[i]) == 3)
			{
				quotes = ft_has_quotes(cmd->files->f_order[i], 0);
				if (quotes != 0)
				{
					locate = ft_find_quotes(cmd->files->f_order[i], 0);
					ft_rm_quotes(&cmd->files->f_order[i], locate);
					free(locate);
				}
				file = ft_create_filename(NULL, 0);
				if (current->files->order[i + 1] == NULL)
					fd = open(mini->files[mini->here_doc_index++],  O_WRONLY | O_CREAT, 0666);
				else
					fd = open(file,  O_WRONLY | O_CREAT, 0666);
				ft_write_fd(env, current->files->f_order[i], fd, quotes);
				close(fd);
				if (current->files->order[i + 1] != NULL)
					unlink(file);
				free(file);
			}
			i++;
		}
		current = current->next;
	}	
}

void	ft_create_files(t_mini *mini, t_cmd *cmd)
{
	t_cmd	*current;
	char	**tmp;
	char	*file;
	int		i;

	current = cmd;
	while (current)
	{
		i = -1;
		while (current->files->order && current->files->order[++i])
		{
			if (ft_atoi(current->files->order[i]) == 3 && (current->files->order[i + 1] == NULL))
			{
				file = ft_create_filename(mini->files, 1);
				if (mini->files != NULL)
				{
					tmp = ft_strstr_dup(mini->files);
					ft_strstr_free(mini->files);
					mini->files = ft_sindub_join(tmp, file);
					ft_strstr_free(tmp);
				}
				else
					mini->files = ft_sindub_join(NULL, file);
				free(file);
			}
		}
		current = current->next;
	}
}

void	ft_here_doc(t_mini *mini, t_cmd *cmd, char **env)
{
	pid_t	pid;
	int		status;

	ft_create_files(mini, cmd);
	ft_strstr_printf(mini->files);
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
}
