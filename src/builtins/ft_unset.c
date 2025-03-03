/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:53:58 by descamil          #+#    #+#             */
/*   Updated: 2025/03/03 19:39:50 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int	ft_find_var_value_unset(char **env, char *arg, size_t len)
{
	char	*str;
	long	name_len;
	int		i;

	i = -1;
	str = ft_strrchr(arg, '=');
	if (!str || ft_isdigit(arg[0]) == 1)
		return (-1);
	name_len = str - arg;
	while (env[++i])
	{
		if (ft_strncmp(env[i], arg, (size_t)name_len) == 0
			&& env[i][name_len] == '=' && len == (size_t)name_len)
			return (i);
	}
	return (-2);
}

static void	ft_unset_cases(t_mini *mini, t_cmd *cmd, int size, int i)
{
	if (ft_strnstr(cmd->args[i], "PWD", 3) && size == 3)
		mini->pwd = 1;
	if (ft_strnstr(cmd->args[i], "OLDPWD", 6) && size == 6)
		mini->oldpwd = 1;
	if (ft_strnstr(cmd->args[i], "PATH", 4) && size == 4)
		mini->path = 1;
}

int	ft_unset(t_mini *mini, t_cmd *cmd)
{
	char	*tmp;
	int		size;
	int		var;
	int		i;

	i = 1;
	while (cmd->args[i])
	{
		size = ft_strlen(cmd->args[i]);
		if (ft_strnstr(cmd->args[i], "_", 1) && size == 1)
			i++;
		if (cmd->args[i] == NULL)
			return (0);
		ft_unset_cases(mini, cmd, size, i);
		tmp = ft_strjoin(cmd->args[i], "=");
		var = ft_find_var_value_unset(mini->env->env, tmp,
				ft_strlen(cmd->args[i]));
		if (var != -1)
			ft_remove_var(&mini->env->env, var);
		free(tmp);
		i++;
	}
	return (0);
}
