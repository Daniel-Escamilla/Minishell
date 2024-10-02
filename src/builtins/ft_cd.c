/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:00:46 by user              #+#    #+#             */
/*   Updated: 2024/10/02 19:36:00 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static int	ft_witch_dot(char *slash)
{
	if ((ft_strnstr(slash, "..", 2) && ft_strlen(slash) == 2) || (ft_strnstr(slash, ".", 1) && ft_strlen(slash) == 1))
		return (2);
	if ((ft_strnstr(slash, "..", 3) && ft_strlen(slash) == 3) || (ft_strnstr(slash, ".", 2) && ft_strlen(slash) == 2))
		return (1);
	return (0);
}

// static int	ft_has_dots(char *str)
// {
// 	char	*slash;
// 	int		i;
	
// 	i = 0;
// 	slash = ft_strrchr(str, '/');
// 	while (ft_strlen(slash) != ft_strlen(str))
// 	{
// 		if (ft_witch_dot(slash) == 1)
// 			i++;
// 		*slash = '\0';
// 		slash = ft_strrchr(str, '/');
// 	}
// 	return (i);
// }

static void	ft_remove_dots(char **var)
{
	char	**string;
	char	*dup;
	int		len;
	int		i;
	int		j;

	i = 0;
	dup = ft_strdup(*var);
	free(dup);
	string = ft_split(*var, '/');
	len = ft_strstr_len(string);
	while (string[i])
	{
		if (ft_witch_dot(string[i]) == 2 && ft_strstr_len(string) == 1)
		{
			printf("%s\n", *string);
			string[0] = NULL;
			string[0] = ft_strdup("/");
			break ;
		}
		// printf("[%s]\n", string[i]);
		if (ft_witch_dot(string[i]) == 2)
		{
			// printf("%s\n", string[i]);
			if (i - 1 == 0)
			{
				// printf("Aqui2\n");
				string[i - 1] = ft_strdup("/");
			}
			if ((i - 1) >= 0)
			{
				j = i;
				while (j >= 0 && string[j] == NULL)
					j--;
				// printf("%d\n", j);
				if (j - 1 > 0)
					string[j - 1] = NULL;
				if (j - 1 == 0)
				{
					// printf("Aqui\n");
					string[j - 1] = ft_strdup("/");
				}
				string[j] = NULL;
			}
		}
		i++;
	}
	i = 0;
	int		rest = 0;
	while (len != 0)
	{
		if (string[i] != NULL)
			rest++;
		i++;
		len--;
	}
	char	*result;
	char	*tmp;
	char	*tmp2;


	result = NULL;
	ft_strstr_printf(string);
	if (string[0][0] == '/')
	{
		free(*var);
		result = ft_strdup("/");
		*var = ft_strdup(result);
		free(result);
		return ;
	}
	tmp = ft_strdup("/");
	tmp2 = ft_strdup("");
	i = 0;
	while (rest != 0)
	{
		printf("%s\n", string[i]);
		if (string[i] != NULL)
		{
			if (result)
				free(result);
			tmp2 = ft_strjoin(string[i], "/");
			result = ft_strjoin(tmp, tmp2);
			free(tmp2);
			if (tmp)
				free(tmp);
			tmp = ft_strdup(result);
			rest--;
		}
		i++;
	}
	free(*var);
	printf("RESULT --> %s\n", result);
	*var = ft_strdup(result);
	free(result);
}

// static char	*ft_save_home(t_mini *mini)
// {
// 	char	*file;
// 	char	*line;

// 	file = ft_sindub_join(NULL, "systemd-path");
// 	line = ft_execute(mini->env->env, file, "/usr/bin/systemd-path", "search-binaries-default:");
// }

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
	if (ft_strncmp(cmd->args[1], "~", 1) == 0 && ft_strlen(cmd->args[1]) == 1)
	{
		tmp = ft_get_var(mini->env->env, "HOME");
		if (tmp == NULL)
			printf("NULL\n");
		// ft_home_save(mini);
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
