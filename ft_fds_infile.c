/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fds_infile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:25:46 by user              #+#    #+#             */
/*   Updated: 2024/09/16 16:06:42 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_more(t_cmd *cmd, int i, int type)
{
	int	j;

	j = 0;
	while (cmd->files->order[i] != NULL)
		if (ft_atoi(cmd->files->order[i++]) == type)
			j++;
	if (j == 1)
		return (j);
	return (0);
}

static int	ft_open_infile(char *filename, t_mini *mini)
{
	int		fd;
	char	*join;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		join = ft_strjoin("mini: ", filename);
		printf("%s: Permission denied\n", join);
		free(join);
		mini->error = -2;
		return (-1);
	}
	mini->error = 0;
	return (fd);
}

static int	ft_process_infile(t_cmd *cmd, t_mini *mini, int i)
{
	int	fd;

	fd = ft_open_infile(cmd->files->f_order[i], mini);
	if (fd == -1)
		return (-1);
	if (ft_more(cmd, i, 1) == 1 && ft_more(cmd, i, 3) == 0)
		return (fd);
	close(fd);
	return (0);
}

int	ft_pick_infile(t_cmd *cmd, t_mini *mini)
{
	int	i;
	int	fd;

	i = 0;
	while (cmd->files->order[i] != NULL)
	{
		if (ft_atoi(cmd->files->order[i]) == 1)
		{
			fd = ft_process_infile(cmd, mini, i);
			if (fd != 0 && ft_more(cmd, i, 1) == 1 && ft_more(cmd, i, 3) == 0)
				return (fd);
		}
		else if (ft_atoi(cmd->files->order[i]) == 3)
		{
			if (ft_more(cmd, i, 3) == 1 && ft_more(cmd, i, 1) == 0)
				return (ft_here_doc(cmd, -2, i));
			fd = ft_here_doc(cmd, 0, i);
		}
		i++;
	}
	return (-1);
}
