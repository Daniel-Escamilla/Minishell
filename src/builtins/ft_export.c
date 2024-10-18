/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:53:49 by descamil          #+#    #+#             */
/*   Updated: 2024/10/18 14:09:55 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static int	ft_export_printf(t_mini *mini)
{
	char	*join;
	char	*var;
	size_t	size;
	int		i;

	i = -1;
	while (mini->env->env[++i])
	{
		join = ft_strchr(mini->env->env[i], '=') + 1;
		size = ft_strlen(mini->env->env[i]) - (ft_strlen(join));
		var = ft_calloc(sizeof(char), size + 1);
		ft_strlcpy(var, mini->env->env[i], size);
		printf("declare -x %s=\"%s\"\n", var, join);
		if (var)
			free(var);
	}
	return (0);
}

int	ft_find_var_value(char **env, char *arg)
{
	char	*str;
	int		i;

	i = -1;
	str = ft_strchr(arg, '=');
	if (!str || ft_strlen(str) == 1 || ft_isdigit(arg[0]) == 1)
		return (-1);
	while (env[++i])
		if (ft_strncmp(env[i], arg, ft_strlen(arg)) == 0)
			return (i);
	return (-2);
}

int	ft_export(t_mini *mini, t_cmd *cmd)
{
	char	**tmp;
	int		var;
	int		i;

	i = 1;
	if (ft_strstr_len(cmd->args) == 1)
		return (ft_export_printf(mini));
	while (cmd->args[i])
	{
		var = ft_find_var_value(mini->env->env, cmd->args[i]);
		if (var != -1)
		{
			ft_remove_var(&mini->env->env, var);
			tmp = ft_strstr_dup(mini->env->env);
			ft_strstr_free(mini->env->env);
			mini->env->env = ft_sindub_join(tmp, cmd->args[i]);
			ft_strstr_free(tmp);
		}
		i++;
	}
	return (0);
}
