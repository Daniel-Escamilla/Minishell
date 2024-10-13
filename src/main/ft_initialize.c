/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:21:54 by smarin-a          #+#    #+#             */
/*   Updated: 2024/10/13 19:45:17 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

char	**ft_strstr_dup_mod(char **str)
{
	char	**dup;
	size_t	i;

	i = 0;
	dup = NULL;
	if (str == NULL)
		return (NULL);
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
		i++;
	}
	return (dup);
}

static t_mini	*ft_free_resources(t_mini *mini, int stage)
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
	mini->env->env = ft_strstr_dup_mod(env);
	if (mini->env->env == NULL)
		return (ft_free_resources(mini, 3));
	mini->flags = ft_calloc(sizeof(t_flags), 1);
	if (mini->flags == NULL)
		return (ft_free_resources(mini, 4));
	mini->token = ft_calloc(sizeof(t_token), 1);
	if (mini->token == NULL)
		return (ft_free_resources(mini, 5));
	mini->fd_history = -1;
	mini->shell_level = 2;
	mini->flags->locate_red = 0;
	mini->flags->expander = 0;
	mini->env->path = NULL;
	mini->token->input = NULL;
	mini->token->tokens = NULL;
	return (mini);
}
