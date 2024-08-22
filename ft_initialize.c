/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:21:54 by smarin-a          #+#    #+#             */
/*   Updated: 2024/08/17 18:12:41 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mini	*ft_initialize(char **env)
{
	t_mini	*mini;

	mini = ft_calloc(sizeof(t_mini), 1);
	if (mini != NULL)
	{
		mini->shell_level = 0;
		mini->env = NULL;
		mini->flags = NULL;
		mini->token = NULL;
		mini->cmd = NULL;
	}
	else
		return (NULL);
	mini->shell_level = 2;
	mini->env = ft_calloc(sizeof(t_env), 1);
	if (mini->env == NULL)
	{
		free(mini);
		return (NULL);
	}
	mini->env->path = NULL;
	mini->env->env = ft_strstr_dup(env);
	mini->flags = ft_calloc(sizeof(t_flags), 1);
	if (mini->flags == NULL)
	{
		ft_strstr_free(mini->env->env);
		free(mini->env);
		free(mini);
		return (NULL);
	}
	mini->flags->locate_red = 0;
	mini->flags->expander = 0;
	mini->token = ft_calloc(sizeof(t_token), 1);
	if (mini->token == NULL)
	{
		free(mini->flags);
		ft_strstr_free(mini->env->env);
		free(mini->env);
		free(mini);
		return (NULL);
	}
	mini->token->input = NULL;
	mini->token->tokens = NULL;
	mini->fd_tmp = 0;
	return (mini);
}
