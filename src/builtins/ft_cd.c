/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:00:46 by user              #+#    #+#             */
/*   Updated: 2025/02/22 11:32:47 by descamil         ###   ########.fr       */
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
	return (trim);
}

static char	*ft_hyphen(t_mini *mini)
{
	char	*rute;

	rute = ft_get_var(mini->env->env, "OLDPWD");
	if (rute == NULL || ft_nothing(rute, 0) == 1)
	{
		write(2, "mini: cd: OLDPWD not set\n", 26);
		g_exit_status = 1;
		free(rute);
		rute = NULL;
	}
	else if (rute != NULL && chdir(rute) != -1)
	{
		write(STDOUT_FILENO, rute, ft_strlen(rute));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (rute);
}

static char	*ft_prepare_path(t_mini *mini, t_cmd *cmd)
{
	char	*rute;

	rute = NULL;
	if (cmd->args[1] == NULL)
	{
		rute = ft_get_var(mini->env->env, "HOME");
		if (rute == NULL)
		{
			write(2, "mini: cd: HOME not set\n", 24);
			g_exit_status = 1;
			free(rute);
			rute = NULL;
		}
		return (rute);
	}
	else if (ft_strncmp(cmd->args[1], "-", 1) == 0
		&& ft_strlen(cmd->args[1]) == 1)
		rute = ft_hyphen(mini);
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

	if (mini->pwd == 1 && mini->oldpwd == 0 && --mini->pwd == 0)
		pwd = ft_strdup("");
	else
		pwd = ft_get_var(mini->env->env, "PWD");
	rute = getcwd(NULL, 0);
	if (rute != NULL)
		ft_change_env(&mini->env->env, "PWD", rute);
	tmp = ft_get_var(mini->env->env, "OLDPWD");
	if (tmp == NULL)
		ft_add_var(&mini->env->env, "OLDPWD=", pwd);
	else if (ft_strlen(tmp) == 0 && mini->oldpwd == 0)
		ft_change_env(&mini->env->env, "OLDPWD", rute);
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
		return ((int)write(2, "bash: cd: too many arguments\n", 30) - 29);
	rute = ft_prepare_path(mini, cmd);
	if (rute == NULL)
		return (1);
	if (chdir(rute) == -1)
	{
		if (cmd->args[1] == NULL)
			return (0);
		else if (ft_strnstr(cmd->args[1], "-", 1) != NULL)
			ft_three_arguments_printf("mini: cd: ", rute,
				": No such file or directory\n");
		else
			ft_three_arguments_printf("mini: cd: ", cmd->args[1],
				": No such file or directory\n");
		free(rute);
		return (1);
	}
	ft_update_env(mini);
	free(rute);
	return (0);
}
