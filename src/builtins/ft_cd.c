/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:00:46 by user              #+#    #+#             */
/*   Updated: 2024/10/01 19:42:49 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static void	ft_remove_dots(char **var)
{
	char	*slash;

	slash = ft_strrchr(*var, '/');
	if (!slash)
		return;
	if ((ft_strnstr(slash, "..", 3) && ft_strlen(slash) == 3) || (ft_strnstr(slash, ".", 2) && ft_strlen(slash) == 2))
	{
		*slash = '\0';
		slash = ft_strrchr(*var, '/');
		printf("%s\n", slash);
		if (ft_strlen(slash) == ft_strlen(*var))
		{
			free(*var);
			*var = ft_strdup("/");
		}
		else if (slash)
			*slash = '\0';
			
	}
}

static char	*ft_prepare_path(t_mini *mini, t_cmd *cmd, char *directorio_actual)
{
	char	*rute;
	char	*tmp;

	rute = NULL;
	tmp = NULL;
	if (ft_strncmp(cmd->args[1], "-", 1) == 0 && ft_strlen(cmd->args[1]) == 1)
	{
		tmp = ft_get_var(mini->env->env, "OLDPWD");
		if (tmp == NULL)
			printf("mini: cd: OLDPWD not set\n");
		else
			printf("%s\n", tmp);
		return (tmp);
	}
	if (cmd->args[1][0] != '/')
	{
		tmp = ft_strjoin("/", cmd->args[1]);
		rute = ft_strjoin(directorio_actual, tmp);
		free(tmp);
	}
	else
		rute = ft_strdup(cmd->args[1]);
	ft_remove_dots(&rute);
	printf("RUTE --> %s\n", rute);
	return (rute);
}

static void	ft_update_env(t_mini *mini, char *rute)
{
	char	*pwd;
	char	*tmp;

	pwd = ft_get_var(mini->env->env, "PWD");
	ft_change_env(&mini->env->env, "PWD", rute);
	tmp = ft_get_var(mini->env->env, "OLDPWD");
	if (tmp == NULL)
		ft_add_var(&mini->env->env, "OLDPWD=", pwd);
	else
		ft_change_env(&mini->env->env, "OLDPWD", pwd);
	free(tmp);
	free(pwd);
}

int	ft_cd(t_mini *mini, t_cmd *cmd)
{
	char	*directorio_actual;
	char	*rute;

	directorio_actual = getcwd(NULL, 0);
	if (ft_strstr_len(cmd->args) >= 3)
		return (-1);
	rute = ft_prepare_path(mini, cmd, directorio_actual);
	if (rute == NULL)
		return (-1);
	if (chdir(rute) == -1)
		dprintf(2, "mini: cd: %s: No such file or directory\n", cmd->args[1]);
	else
		ft_update_env(mini, rute);
	free(directorio_actual);
	free(rute);
	return (1);
}
