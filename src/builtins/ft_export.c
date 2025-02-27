/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:00:37 by descamil          #+#    #+#             */
/*   Updated: 2025/02/27 13:58:02 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int ft_find_var_value_export(char **env, char *arg, int quotes)
{
    char    *str;
    long    name_len;
    int     i;

    i = -1;
    str = ft_strchr(arg, '=');
    if (!str || ft_isdigit(arg[0]) == 1 || (str[0] == '\0' && quotes == 0))
        return (-1);
    name_len = str - arg;
	if (g_exit_status == 1)
		return (-1);
    while (env[++i])
    {
        if (ft_strncmp(env[i], arg, (size_t)name_len) == 0 && env[i][name_len] == '=')
            return (i);
    }
    return (-2);
}

int	ft_export(t_mini *mini, t_cmd *cmd)
{
	char	**tmp;
	int		var;
	int		i;

	i = 1;
	if (ft_strstr_len(cmd->args) == 1)
		return (ft_print_order(mini->env->env));
	while (cmd->args[i])
	{
		if (cmd->args[i][0] == '=')
		{
			write(2, "mini: export: `", 16);
			write(2, cmd->args[i], ft_strlen(cmd->args[i]));
			write(2, "': not a valid identifier\n", 27);
			g_exit_status = 1;
			return (1);
		}
		if (ft_strnstr(cmd->args[i], "OLDPWD", 6))
			mini->oldpwd = 0;
		if (ft_strnstr(cmd->args[i], "PATH", 4))
			mini->path = 0;
		var = ft_find_var_value_export(mini->env->env, cmd->args[i], ft_atoi(cmd->export_quotes[i]));
		if (ft_strnstr(cmd->args[i], "_", 1) && ft_strlen(cmd->args[i]) == 1)
			var = -1;
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
