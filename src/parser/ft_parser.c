/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:36:51 by user              #+#    #+#             */
/*   Updated: 2024/07/23 14:37:08 by user             ###   ########.fr       */
/*                                                							  */
/* ************************************************************************** */

#include "../../include/parser.h"

char	**ft_create_path(char **env)
{
	char	**path;
	int		i;

	i = -1;
	path = NULL;
	while (env[++i] != NULL)
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			path = ft_split(env[i] + 5, ':');
	}
	return (path);
}

int	ft_sizes(t_cmd *current)
{
	char	**tmp;
	int		size;
	int		i;

	i = -1;
	size = 0;
	tmp = ft_strstr_dup(current->args);
	while (tmp[++i])
	{
		if (ft_type(tmp[i]) != 0)
			i++;
		else
			size++;
	}
	ft_strstr_free(tmp);
	return (size);
}

void	ft_start_val(t_cmd *cmd)
{
	cmd->names->fd = 0;
	cmd->names->fd_infile = 0;
	cmd->names->fd_outfile = 1;
}

int	ft_wait_bonus(t_mini *mini)
{
	int	state;
	int	i;

	i = 0;
	state = 0;
	if (mini->proc[i + 1])
		while (mini->proc[i + 1])
			waitpid(mini->proc[i++], NULL, 0);
	waitpid(mini->proc[i], &state, 0);
	printf(B_GR_0"%d\n"RESET, state);
	g_exit_status = state;
	if (state >= 256)
	{
		state /= 256;
		g_exit_status = state;
	}
	if (state == 139)
		g_exit_status = state;
	return (state);
}
