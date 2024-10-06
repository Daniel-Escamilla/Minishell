/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:00:46 by user              #+#    #+#             */
/*   Updated: 2024/10/05 13:57:59 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static char	*ft_save_home(t_mini *mini)
{
	char	*line;
	char	**file;
	char	*trim;

	file = ft_sindub_join(NULL, "systemd-path");
	line = ft_execute(mini->env->env, file, "/usr/bin/systemd-path", "user: ");
	ft_strstr_free(file);
	trim = ft_strtrim(line + 6, "\n");
	free(line);
	if (trim == NULL)
		return (NULL);
	printf("%s\n", trim);
	return (trim);
}

static char	*ft_prepare_path(t_mini *mini, t_cmd *cmd)
{
	char	*rute;

	rute = NULL;
	if (cmd->args[1] == NULL)
	{
		rute = ft_get_var(mini->env->env, "HOME");
		if (rute == NULL)
			printf("mini: cd: HOME not set\n");
		return (rute);
	}
	else if (ft_strncmp(cmd->args[1], "-", 1) == 0
		&& ft_strlen(cmd->args[1]) == 1)
	{
		rute = ft_get_var(mini->env->env, "OLDPWD");
		if (rute == NULL)
			printf("mini: cd: OLDPWD not set\n");
		else
			printf("%s\n", rute);
		return (rute);
	}
	else if (cmd->args[1][0] == '~' && ft_strlen(cmd->args[1]) == 1)
		rute = ft_save_home(mini);
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
	{
		write(2, "bash: cd: too many arguments\n", 30);
		return (-1);
	}
	rute = ft_prepare_path(mini, cmd);
	if (rute == NULL)
		return (-1);
	if (chdir(rute) == -1)
		ft_error_in_child("mini: cd: ", cmd->args[1],
			": No such file or directory\n");
	else
		ft_update_env(mini);
	free(rute);
	return (0);
}
