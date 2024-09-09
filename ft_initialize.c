/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:21:54 by smarin-a          #+#    #+#             */
/*   Updated: 2024/09/03 12:10:16 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mini	*ft_free_resources(t_mini *mini, int stage)
{
	if (stage <= 5)
		free(mini->flags);
	if (stage <= 3)
		ft_strstr_free(mini->env->env);
	if (stage <= 4)
		free(mini->env);
	if (stage <= 2)
		free(mini);
	return (NULL);
}

t_mini	*ft_initialize(char **env)
{
	t_mini	*mini;

	mini = ft_calloc(sizeof(t_mini), 1);
	if (mini == NULL)
		return (NULL);
	mini->env = ft_calloc(sizeof(t_env), 1);
	if (mini->env == NULL)
		return (ft_free_resources(mini, 2));
	mini->env->env = ft_strstr_dup(env);
	if (mini->env->env == NULL)
		return (ft_free_resources(mini, 3));
	mini->flags = ft_calloc(sizeof(t_flags), 1);
	if (mini->flags == NULL)
		return (ft_free_resources(mini, 4));
	mini->token = ft_calloc(sizeof(t_token), 1);
	if (mini->token == NULL)
		return (ft_free_resources(mini, 5));
	mini->fd_history = 0;
	mini->shell_level = 2;
	mini->flags->locate_red = 0;
	mini->flags->expander = 0;
	mini->env->path = NULL;
	mini->token->input = NULL;
	mini->token->tokens = NULL;
	mini->fd_tmp = 0;
	return (mini);
}
