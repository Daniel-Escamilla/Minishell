/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fds_outfile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 09:19:54 by descamil          #+#    #+#             */
/*   Updated: 2024/09/12 19:35:25 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handle_trunc(t_cmd *cmd, t_mini *mini, int i)
{
	char	*join;
	int		fd;

	fd = open(cmd->files->f_order[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		join = ft_strjoin("mini: ", cmd->files->f_order[i]);
		perror(join);
		free(join);
		mini->error = -2;
		return (-1);
	}
	if (ft_more(cmd, i, 2) == 1 && ft_more(cmd, i, 4) == 0)
		return (fd);
	close(fd);
	return (0);
}

int	ft_handle_append(t_cmd *cmd, t_mini *mini, int i)
{
	char	*join;
	int		fd;

	fd = open(cmd->files->f_order[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		join = ft_strjoin("mini: ", cmd->files->f_order[i]);
		perror(join);
		free(join);
		mini->error = -2;
		return (-1);
	}
	if (ft_more(cmd, i, 4) == 1 && ft_more(cmd, i, 2) == 0)
		return (fd);
	close(fd);
	return (0);
}

int	ft_pick_outfile(t_cmd *cmd, t_mini *mini)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	while (cmd->files->order[i] != NULL)
	{
		if (ft_atoi(cmd->files->order[i]) == 2)
		{
			fd = ft_handle_trunc(cmd, mini, i);
			if (fd != 0)
				return (fd);
		}
		else if (ft_atoi(cmd->files->order[i]) == 4)
		{
			fd = ft_handle_append(cmd, mini, i);
			if (fd != 0)
				return (fd);
		}
		i++;
	}
	return (-1);
}