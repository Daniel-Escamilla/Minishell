/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:27:49 by user              #+#    #+#             */
/*   Updated: 2024/08/17 17:55:31 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_t_env(t_env **env)
{
	int i;
	
	i = 0;
	if (env && *env)
	{
		if ((*env)->path)
			free((*env)->path);
		if ((*env)->env)
		{
			while ((*env)->env[i])
				free((*env)->env[i++]);
		}
	}
	free(*env);
}

void	free_t_cmd(t_cmd **cmd)
{
	t_cmd	*current;
	t_cmd	*next;
	
	current = *cmd;
	while (current)
	{
		next = current->next;
		ft_strstr_free(current->args);
		if (current->files)
		{
			if (current->files->f_order)
				ft_strstr_free(current->files->f_order);
			if (current->files->order)
				ft_strstr_free(current->files->order);
			free(current->files);
		}
		if (current->type)
		{
			if (current->type->in)
				free(current->type->in);
			if (current->type->out)
				free(current->type->out);
			free(current->type);
		}
		if (current->names)
		{
			if (current->names->proc)
				free(current->names->proc);
			free(current->names);
		}
		free(current->cmd);
		free(current);
		current = next;
	}
	*cmd = NULL;
}

void free_t_mini(t_mini *mini)
{
	if (mini == NULL)
		return;
	if (mini->env != NULL) 
	{
		if (mini->env->path != NULL)
		{
			free(mini->env->path);
			mini->env->path = NULL;
		}
		if (mini->env->env != NULL)
			ft_strstr_free(mini->env->env);
	}
	if (mini->flags)
		free(mini->flags);
	if (mini->token != NULL)
	{
		if (mini->token->input != NULL)
			free(mini->token->input);
		if (mini->token->tokens != NULL)
			ft_strstr_free(mini->token->tokens);
		free(mini->token);
	}
	if (mini->env)
		free(mini->env);
	free(mini);
}
