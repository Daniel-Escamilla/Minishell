/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_upgrade_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:44:59 by descamil          #+#    #+#             */
/*   Updated: 2024/10/24 11:50:20 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

static char	**ft_create_default_env(void)
{
	char	**env;
	char	*join;
	char	*pwd;
	int		i;

	env = (char **)ft_calloc(sizeof(char *), 4);
	if (env == NULL)
		return (NULL);
	pwd = getcwd(NULL, 0);
	join = ft_strjoin("PWD=", pwd);
	env[0] = ft_strdup(join);
	env[1] = ft_strdup("SHLVL=1");
	env[2] = ft_strdup("_=/usr/bin/env");
	free(join);
	i = -1;
	while (++i < 3)
	{
		if (env[i] == NULL)
		{
			ft_strstr_free(env);
			return (NULL);
		}
	}
	return (env);
}

static void	ft_update_shlvl(char ***dup, size_t i)
{
	char	*value;
	long	tmp;

	value = ft_get_var(*dup, "SHLVL");
	tmp = ft_atoi(value) + 1;
	free(value);
	value = ft_itoa(tmp);
	free((*dup)[i]);
	(*dup)[i] = ft_strjoin("SHLVL=", value);
	free(value);
}

static void	ft_update_pwd(char ***dup, size_t i)
{
	char	*current_value;
	char	*current_pwd;

	current_value = ft_get_var(*dup, "PWD");
	current_pwd = getcwd(NULL, 0);
	if (current_value == NULL || ft_strncmp(current_value
			, current_pwd, ft_strlen(current_pwd)) != 0)
	{
		free((*dup)[i]);
		(*dup)[i] = ft_strjoin("PWD=", current_pwd);
	}
	free(current_value);
	free(current_pwd);
}

char	**ft_upgrade_env(char **str)
{
	char	**dup;
	size_t	i;

	i = 0;
	dup = NULL;
	if (*str == NULL)
		return (ft_create_default_env());
	dup = (char **)ft_calloc(sizeof(char *), (size_t)ft_strstr_len(str) + 1);
	if (dup == NULL)
		return (NULL);
	while (i < (size_t)ft_strstr_len(str))
	{
		dup[i] = ft_strdup(str[i]);
		if (dup[i] == NULL)
		{
			ft_strstr_free(dup);
			return (NULL);
		}
		if (ft_strncmp(dup[i], "SHLVL=", 6) == 0)
			ft_update_shlvl(&dup, i);
		if (ft_strncmp(dup[i], "PWD=", 4) == 0)
			ft_update_pwd(&dup, i);
		i++;
	}
	return (dup);
}
