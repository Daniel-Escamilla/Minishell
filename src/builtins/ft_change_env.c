/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:05:18 by user              #+#    #+#             */
/*   Updated: 2024/10/11 14:21:25 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

void	ft_change_env(char ***env, char *variable, char *content)
{
	int		i;
	char	*join;
	char	*new_value;

	i = -1;
	if (content == NULL || variable == NULL)
		return ;
	join = ft_strjoin(variable, "=");
	if (!join)
		return ;
	while ((*env)[++i] != NULL)
	{
		if (ft_strnstr((*env)[i], join, ft_strlen(join)))
		{
			new_value = ft_strjoin(join, content);
			if (!new_value)
				break ;
			free((*env)[i]);
			(*env)[i] = ft_strdup(new_value);
			free(new_value);
			break ;
		}
	}
	free(join);
}

char	*ft_get_var(char **env, char *variable)
{
	char	*var;
	char	*tmp;
	int		i;

	i = -1;
	tmp = ft_strjoin(variable, "=");
	var = NULL;
	while (env[++i])
	{
		if (ft_strnstr(env[i], tmp, ft_strlen(tmp)))
			var = ft_strdup(env[i] + ft_strlen(variable) + 1);
	}
	free(tmp);
	return (var);
}

void	ft_add_var(char ***env, char *variable, char *content)
{
	char	**env_tmp;
	char	*var;
	char	*tmp;

	if (content == NULL || variable == NULL)
		return ;
	env_tmp = ft_strstr_dup(*env);
	ft_strstr_free(*env);
	var = ft_strdup(variable);
	tmp = ft_strjoin(var, content);
	free(var);
	*env = ft_sindub_join(env_tmp, tmp);
	free(tmp);
	ft_strstr_free(env_tmp);
}

void	ft_remove_var(char ***env, int i)
{
	char	**env_tmp;
	int		size;
	int		j;
	int		k;

	k = 0;
	j = -1;
	env_tmp = ft_strstr_dup(*env);
	ft_strstr_free(*env);
	size = ft_strstr_len(env_tmp);
	if (i == -2)
    	*env = ft_calloc(sizeof(char *), size + 1);
	else
    	*env = ft_calloc(sizeof(char *), size);
	while (++j < size)
		if (j != i)
			(*env)[k++] = ft_strdup(env_tmp[j]);
	(*env)[k] = NULL;
	ft_strstr_free(env_tmp);
}
