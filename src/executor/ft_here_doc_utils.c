/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 20:39:20 by descamil          #+#    #+#             */
/*   Updated: 2025/03/03 17:35:08 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

static void	ft_break_hd(char *line, char *eof, int j)
{
	if (line == NULL)
		printf("mini: warning: here-document at line %d delimited by"
			"end-of-file (wanted `%s')\n", j, eof);
	else
		free(line);
}

static void	ft_write_fd(t_mini *mini, char *eof, int fd, int quotes)
{
	char	*line;
	char	*tmp;
	int		j;

	j = 0;
	while (1)
	{
		line = readline("> ");
		if (line == NULL || (ft_strnstr(line, eof, ft_strlen(line))
				&& ft_strlen(eof) == ft_strlen(line)))
		{
			ft_break_hd(line, eof, j);
			break ;
		}
		if (quotes == 0)
		{
			tmp = ft_expander(mini, line);
			free(line);
			line = tmp;
		}
		if (write(fd, line, ft_strlen(line)) == -1 || write(fd, "\n", 1) == -1)
			printf("Error write");
		free(line);
		j++;
	}
}

static void	ft_clean_name(t_cmd *cmd, int quotes, int i)
{
	int	*locate;

	if (quotes != 0)
	{
		locate = ft_find_quotes(cmd->files->f_order[i], 0);
		ft_rm_quotes(&cmd->files->f_order[i], locate);
		free(locate);
	}
}

static int	fd_open(t_mini *mini, t_cmd *current, char *file, int i)
{
	int	fd;

	if (current->files->order[i + 1] == NULL)
		fd = open(mini->files[mini->here_doc_index++],
				O_WRONLY | O_CREAT, 0666);
	else
		fd = open(file, O_WRONLY | O_CREAT, 0666);
	return (fd);
}

void	ft_write_here_doc(t_mini *mini, t_cmd *current, int i)
{
	char	*file;
	int		quotes;
	int		fd;

	quotes = ft_has_quotes(current->files->f_order[i], 0);
	ft_clean_name(current, quotes, i);
	file = ft_create_filename(NULL, 0);
	fd = fd_open(mini, current, file, i);
	ft_write_fd(mini, current->files->f_order[i], fd, quotes);
	close(fd);
	if (ft_more(current, i, 3) != 1 || ft_more(current, i, 1) != 0)
		unlink(file);
	free(file);
}
