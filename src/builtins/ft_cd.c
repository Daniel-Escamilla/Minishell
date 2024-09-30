/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:00:46 by user              #+#    #+#             */
/*   Updated: 2024/09/30 19:15:17 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

char *ft_change_route(char *arg1, char *arg2, char *dir)
{
	char *start_pos;
	size_t prefix_len;
	size_t arg1_len;
	size_t arg2_len;
	char *result;

	start_pos = ft_strnstr(dir, arg1, ft_strlen(dir));
	if (!start_pos)
		return (NULL);
	arg1_len = ft_strlen(arg1);
	arg2_len = ft_strlen(arg2);
	prefix_len = start_pos - dir;
	result = ft_calloc(1, prefix_len + arg2_len + ft_strlen(start_pos + arg1_len) + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, dir, prefix_len);
	ft_memcpy(result + prefix_len, arg2, arg2_len);
	ft_strlcpy(result + prefix_len + arg2_len, start_pos + arg1_len,
		ft_strlen(start_pos + arg1_len) + 1);
	return (result);
}

int	ft_cd(t_mini *mini, t_cmd *cmd)
{
	char	*directorio_actual;
	char	*ruta;
	int		size;
	
	directorio_actual = getcwd(NULL, 0);
	printf("%s\n", directorio_actual);
	printf(B_OR_0"");
	ft_strstr_printf(cmd->args);
	printf(""RESET);
	size = ft_strstr_len(cmd->args);
	if (size >= 4)
	{
		free(directorio_actual);
		printf("cd: too many arguments\n");
		return (-1);
	}
	else if (size == 3)
	{
		ruta = ft_change_route(cmd->args[1], cmd->args[2], directorio_actual);
		printf("%s\n", ruta);
		if (chdir(ruta) == -1)
			printf("ERROR\n");
		else
			ft_change_env(mini->env->env, "PWD", ruta);
		free(ruta);
	}
	else if (size == 2)
	{
		
	}
	else if (size == 1)
	{
		
	}
	free(directorio_actual);
	return (1);
}
