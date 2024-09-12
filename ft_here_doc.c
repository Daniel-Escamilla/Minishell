/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 09:32:44 by descamil          #+#    #+#             */
/*   Updated: 2024/09/12 19:03:51 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_create_filename(void)
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
	return (filename);
}

static int	ft_write_in_fd(t_cmd *cmd, int i)
{
	char	*line;
	int		fd_tmp;

	fd_tmp = open(cmd->names->join, O_WRONLY | O_CREAT, 0666);
	if (fd_tmp == -1)
		ft_error("Error open", 2);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			ft_error("Error readline", 2);
		if (ft_strnstr(line, cmd->files->f_order[i], ft_strlen(line))
			&& ft_strlen(cmd->files->f_order[i]) == ft_strlen(line))
		{
			free(line);
			break ;
		}
		if (write(fd_tmp, line, ft_strlen(line)) == -1
			|| write(fd_tmp, "\n", 1) == -1)
			ft_error("Error write", 2);
		free(line);
	}
	return (fd_tmp);
}

static int	ft_handle_last_hd(t_cmd *cmd, int last)
{
	int	fd;

	fd = -1;
	if (last == -2)
	{
		fd = open(cmd->names->join, O_RDONLY);
		if (fd == -1)
			ft_error("Error opening file", 2);
	}
	else
		unlink(cmd->names->join);
	return (fd);
}

int	ft_here_doc(t_cmd *cmd, int last, int i)
{
	int	fd_tmp;
	int	fd;

	cmd->names->join = ft_create_filename();
	fd_tmp = ft_write_in_fd(cmd, i);
	close(fd_tmp);
	fd = ft_handle_last_hd(cmd, last);
	free(cmd->names->join);
	return (fd);
}
