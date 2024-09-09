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

#include "minishell.h"

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

void	ft_select_cmd(t_cmd *current, t_mini *mini, int j)
{
	char	**tmp2;
	char	**tmp;
	int		size;
	int		i;

	i = -1;
	size = 0;
	tmp = ft_strstr_dup(current->args);
	if (tmp == NULL)
		mini->cmd->files->error = -1;
	while (tmp[++i] && ft_type(tmp[i]) != 0)
		size++;
	i = -1;
	tmp2 = ft_calloc(sizeof(char *),
			ft_strstr_len(current->args) + 1 - (size * 2));
	if (tmp2 == NULL)
		mini->cmd->files->error = -1;
	while (tmp[++i])
	{
		current->error = 0;
		if (ft_type(tmp[i]) != 0)
			i++;
		else if (j == -1 && j++ > -2)
		{
			current->cmd = ft_builtins(current, tmp[i]);
			if (current->cmd == NULL)
				current->cmd = ft_route_cmd(mini, current, tmp[i]);
			if (current->cmd == NULL && current->error != -2)
				mini->cmd->files->error = -1;
		}
		else if (current->error != -2 && j < ft_strstr_len(current->args))
		{
			tmp2[j] = ft_strdup(tmp[i]);
			if (tmp2[j++] == NULL)
				mini->cmd->files->error = -1;
		}
	}
	ft_strstr_free(current->args);
	current->args = NULL;
	current->args = ft_strstr_dup(tmp2);
	if (current->args == NULL)
		mini->cmd->files->error = -1;
	ft_strstr_free(tmp2);
	ft_strstr_free(tmp);
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
	while (mini->proc[i + 1])
		waitpid(mini->proc[i++], NULL, 0);
	waitpid(mini->proc[i], &state, 0);
	return (state);
}
