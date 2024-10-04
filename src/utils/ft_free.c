/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:27:49 by user              #+#    #+#             */
/*   Updated: 2024/10/05 00:17:45 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

static void	ft_free_sim(void *ptr, char *str, char *str1)
{
	if (str)
		free(str);
	if (str1)
		free(str1);
	free (ptr);
}

static void	ft_free_dou(void *ptr, char **str, char **str1)
{
	if (str)
		ft_strstr_free(str);
	if (str1)
		ft_strstr_free(str1);
	free (ptr);
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
		ft_strstr_free(current->quote_args);
		if (current->files)
			ft_free_dou(current->files,
				current->files->f_order, current->files->order);
		if (current->type)
			ft_free_sim(current->type,
				current->type->in, current->type->out);
		if (current->names)
			free(current->names);
		free(current->cmd);
		free(current);
		current = next;
	}
	*cmd = NULL;
}

void	free_t_mini(t_mini *mini)
{
	if (mini == NULL)
		return ;
	if (mini->env != NULL)
	{
		if (mini->env->path != NULL)
			free(mini->env->path);
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
	close(2);
	close(1);
	close(0);
}
