/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:53:58 by descamil          #+#    #+#             */
/*   Updated: 2024/10/22 15:59:39 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int	ft_unset(t_mini *mini, t_cmd *cmd)
{
	char	*tmp;
	int		var;
	int		i;

	i = 1;
	while (cmd->args[i])
	{
		tmp = ft_strjoin(cmd->args[i], "=");
		printf("%s\n", tmp);
		var = ft_find_var_value(mini->env->env, tmp);
		if (var != -1)
		{
			printf("Aquí\n");
			ft_remove_var(&mini->env->env, var);
		}
		free(tmp);
		i++;
	}
	return (0);
}
