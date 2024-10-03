/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:00:46 by user              #+#    #+#             */
/*   Updated: 2024/10/03 19:34:48 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static char	*ft_prepare_path(t_mini *mini, t_cmd *cmd)
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
	else if (ft_strncmp(cmd->args[1], "~", 1) == 0 && ft_strlen(cmd->args[1]) == 1)
	{
		tmp = ft_get_var(mini->env->env, "HOME");
		if (tmp == NULL)
			printf("NULL\n");
		// ft_home_save(mini);
	}
	else
		rute = ft_strdup(cmd->args[1]);
	return (rute);
}

static void	ft_update_env(t_mini *mini)
{
	char	*pwd;
	char	*rute;
	char	*tmp;

	pwd = ft_get_var(mini->env->env, "PWD");
	rute = getcwd(NULL, 0);
	if (rute != NULL)
		ft_change_env(&mini->env->env, "PWD", rute);
	else
		ft_change_env(&mini->env->env, "PWD", "");
	tmp = ft_get_var(mini->env->env, "OLDPWD");
	if (tmp == NULL)
		ft_add_var(&mini->env->env, "OLDPWD=", pwd);
	else
		ft_change_env(&mini->env->env, "OLDPWD", pwd);
	free(rute);
	free(tmp);
	free(pwd);
}

int	ft_cd(t_mini *mini, t_cmd *cmd)
{
	char	*rute;

	if (ft_strstr_len(cmd->args) >= 3)
		return (-1);
	rute = ft_prepare_path(mini, cmd);
	if (rute == NULL)
		return (-1);
	if (chdir(rute) == -1)
	// if (chdir(cmd->args[1]) == -1)
		dprintf(2, "mini: cd: %s: No such file or directory\n", cmd->args[1]);
	else
		ft_update_env(mini);
	free(rute);
	return (0);
}

int	ft_env(t_mini *mini)
{
	ft_strstr_printf(mini->env->env);
	return (0);
}