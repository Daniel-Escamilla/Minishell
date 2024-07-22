/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:22:30 by smarin-a          #+#    #+#             */
/*   Updated: 2024/07/11 09:39:13 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_fill_matrix_pipes(char *input, char **splited_pipes)
{
	int	i;
	int	init;
	int	position;

	i = -1;
	init = 0;
	position = 0;
	while (input[++i])
	{
		if (input[i] == 34 || input[i] == 39)
			i = ft_locate_next_quote(i + 1, input, input[i]) + 1;
		if ((input[i + 1] == '|' || input[i + 1] == '\0') && input[i] != '|')
		{
			splited_pipes[position] = ft_substr(input, init, i - init + 1);
			if (splited_pipes[position] == NULL)
				ft_exit_error(NULL, "Malloc error", 54);
			position++;
		}
		if (input[i] == '|' && (input[i + 1] != '|' || input[i + 1] != '\0'))
			init = i + 1;
		splited_pipes[position] = NULL;
		return (splited_pipes);
	}
	return (NULL);
}

int	ft_pipe_error(char *input, int i)
{
	while (input[i] != '\0')
	{
		while (input[i] == ' ')
			i++;
		if (input[i] == '|' || input[i] == '\0')
			return (-1);
		else
			return (1);
	}
	return (-1);
}

int	ft_count_pipes(char *input)
{
	int	i;
	int	amount;
	int	character;

	i = 0;
	amount = 0;
	character = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			i = ft_locate_next_quote(i + 1, input, input[i]) + 1;
		if (input[i] == '|')
		{
			character = ft_pipe_error(input, i + 1);
			amount++;
		}
		if ((character == -1 || (input[i] == '|' && (input[i + 1] == '|' || input[i + 1] == '\0' || ft_nothing(input, i + 1) == 1 || ft_nothing_r(input, i + 1) == 1)) || input[0] == '|'))
		{
			ft_put_error("mini", NULL, "syntax error near unexpected token `|'");
			g_exit_status = 258;
			return (-1);
		}
		if (input[i] == '\0')
			return (amount);
		i++;
	}
	return (amount);
}

int	ft_check_pipes_arg(char *input)
{
	int	i;
	int	result;

	i = -1;
	result = -1;
	while (input[++i])
	{
		if (input[i] != ' ' && input[i] != '\t' && input[i] != '\n')
			result = 0;
	}
	if (result == -1)
		ft_put_error("mini", NULL, "syntax error near unexpected token `||'");
	return (result);
}

char	**ft_split_pipes(char *input)
{
	char	**splited_pipes;
	int		i;

	i = -1;
	splited_pipes = ft_calloc(sizeof(char *), (ft_count_pipes(input) + 2));
	if (!splited_pipes)
		ft_exit_error(NULL, "Malloc error", 54);
	splited_pipes = ft_fill_matrix_pipes(input, splited_pipes);
	while (splited_pipes[++i])
	{
		if (ft_check_pipes_arg(splited_pipes[i]) == -1)
		{
			g_exit_status = 258;
			while (i >= 0)
				free(splited_pipes[i--]); // Utilizar free_strstr
			free(splited_pipes);
			return (NULL);
		}
	}
	return (splited_pipes);
}
