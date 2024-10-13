/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:53:49 by descamil          #+#    #+#             */
/*   Updated: 2024/10/13 14:58:46 by descamil         ###   ########.fr       */
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

int	ft_dup_var(t_mini *mini, char *arg)
{
	char	*str;
	int		size;
	int		i;

	i = -1;
	str = ft_strchr(arg, '=');
	size = (int)(str - arg);
	if (size == 0 || !str || ft_isdigit(arg[0]) == 1)
		return (-1);
	while (mini->env->env[++i])
		if (ft_strncmp(mini->env->env[i], arg, (size_t)size + 1) == 0)
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
		var = ft_dup_var(mini, cmd->args[i]);
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
