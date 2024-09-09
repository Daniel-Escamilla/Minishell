/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 09:19:54 by descamil          #+#    #+#             */
/*   Updated: 2024/09/03 09:35:00 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_more(t_cmd *cmd, int i, int type)
{
	int	j;

	j = 0;
	while (cmd->files->order[i] != NULL)
	{
		if (ft_atoi(cmd->files->order[i]) == type)
			j++;
		i++;
	}
	if (j == 1)
		return (j);
	return (0);
}

int	ft_pick_infile(t_cmd *cmd, t_mini *mini)
{
	int		i;
	int		fd;
	char	*join;

	i = 0;
	while (cmd->files->order[i] != NULL)
	{
		if (ft_atoi(cmd->files->order[i]) == 1)
		{
			fd = open(cmd->files->f_order[i], O_RDONLY);
			if (fd == -1)
			{
				join = ft_strjoin("mini: ", cmd->files->f_order[i]);	
				perror(join);
				free(join);
				// mini->error = -2;
				return (-1);
			}
			if (ft_more(cmd, i, 1) == 1)
				return (fd);
			close(fd);
		}
		if (ft_atoi(cmd->files->order[i]) == 3)
		{
			if (ft_more(cmd, i, 3) == 1)
				return (ft_here_doc(cmd, mini, -2, i));
			fd = ft_here_doc(cmd, mini, 0, i);
		}
		i++;
	}
	return (-1);
}

int	ft_pick_outfile(t_cmd *cmd, t_mini *mini)
{
	int		i;
	int		fd;
	char	*join;

	i = 0;
	fd = 0;
	while (cmd->files->order[i] != NULL)
	{
		if (ft_atoi(cmd->files->order[i]) == 2)
		{
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
		}
		if (ft_atoi(cmd->files->order[i]) == 4)
		{
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
		}
		i++;
	}
	return (-1);
}

