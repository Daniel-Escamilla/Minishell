/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 09:32:44 by descamil          #+#    #+#             */
/*   Updated: 2024/09/09 11:20:29 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_create_file(t_cmd *cmd)
{
	int		index;
	char	*number;

	index = 0;
	number = NULL;
	cmd->names->join = ft_strdup(".here_doc");
	while (access(cmd->names->join, F_OK) != -1)
	{
		free(cmd->names->join);
		if (number)
			free(number);
		number = ft_itoa(index++);
		cmd->names->join = ft_strjoin(".here_doc", number);
	}
	free(number);
}

int	ft_here_doc(t_cmd *cmd, int last, int i)
{
	char	*line;
	int		fd_tmp;
	int		fd;

	fd = -1;
	ft_create_file(cmd);
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
	close(fd_tmp);
	if (last == -2)
	{
		fd = open(cmd->names->join, O_RDONLY);
		if (fd == -1)
			ft_error("Error opening file", 2);
		return (fd);
	}
	else
		unlink(cmd->names->join);
	free(cmd->names->join);
	return (fd);
}
