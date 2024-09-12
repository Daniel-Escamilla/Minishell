/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:50:54 by smarin-a          #+#    #+#             */
/*   Updated: 2024/09/12 19:18:36 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_void_input(char *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i] != '\0')
		j += ft_isspace(input[i++]);
	if (j == i)
		return (-1);
	return (0);
}

char	*ft_free_input(t_mini *mini, char *input)
{
	int	j;

	j = 0;
	while (input && input[j] == ' ')
		j++;
	if (input[j] != '\0')
	{
		if (mini->cmd)
		{
			if (mini->cmd->args)
			{
				j = 0;
				while (mini->cmd->args[j] && mini->cmd->args[j] != NULL)
					ft_strstr_free(mini->cmd->args);
			}
		}
	}
	free(input);
	return (NULL);
}

int	ft_find_exit(char *input)
{
	char	*exit_position;

	exit_position = ft_strnstr(input, "exit", ft_strlen(input));
	if (exit_position != NULL)
	{
		exit_position += 4;
		while (*exit_position == ' ')
			exit_position++;
		if (*exit_position == '\0')
			return (1);
	}
	return (0);
}

void	ft_free_per_comm(t_mini *mini, char *input)
{
	if (mini->input)
	{
		free(mini->input);
		mini->input = NULL;
	}
	if (mini->flags->redirect && input != NULL)
	{
		mini->flags->locate_red = 0;
		free(mini->flags->redirect);
		mini->flags->redirect = NULL;
	}
	if (mini->proc && mini->error != -2 && input[0] != '\0')
		free(mini->proc);
	if (input)
		free(input);
}

void	ft_recive_input(t_mini *mini)
{
	char	*input;

	mini->fd_history = ft_history();
	while (1)
	{
		input = readline("🐚"B_GR_0" MINI(S)HELL"RESET" 🔥 -> ");
		if (!input)
			ft_exit_error(mini, "Exit", g_exit_status);
		if (ft_check_void_input(input) == -1 || input[0] == '\0')
			(void)input;
		else
		{
			mini->input = ft_strdup(input);
			add_history(input);
			if (mini->fd_history != -1)
				if (write(mini->fd_history, input, ft_strlen(input)) == -1
					|| write(mini->fd_history, "\n", 1) == -1)
					return ;
			if (ft_strtok(mini, &(mini->cmd), input) == 0)
				printf("\nLlega al final! 🚀\n\n");
		}
		ft_free_per_comm(mini, input);
		free_t_cmd(&(mini->cmd));
	}
	close(mini->fd_history);
}
