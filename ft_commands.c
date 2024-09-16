/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:31:25 by smarin-a          #+#    #+#             */
/*   Updated: 2024/09/16 13:03:34 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_args(char *input)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (input[i] != '\0')
	{
		while (input[i] == ' ' && input[i] != '\0')
			i++;
		if (input[i] == '\0')
			return (size);
		while (input[i] != ' ' && input[i] != '\0')
		{
			if (input[i] == '\'' || input[i] == '\"')
				i = ft_locate_next_quote(i + 1, input, input[i]);
			i++;
		}
		size++;
	}
	return (size);
}

int	is_red(char *argv)
{
	int	j;
	int	red;

	j = 0;
	red = 0;
	while (argv[j] != '\0')
	{
		if (argv[j] == '\'' || argv[j] == '\"')
			j = ft_locate_next_quote(j + 1, argv, argv[j]);
		red = is_redirection(argv[j], argv[j + 1]);
		if (red != 0)
			return (red);
		j++;
	}
	return (0);
}

t_cmd	*ft_add_command(char *input, int i)
{
	t_cmd	*new_cmd;

	new_cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!new_cmd)
		ft_error("Calloc error", 9);
	new_cmd->names = ft_calloc(sizeof(t_names), 1);
	if (!new_cmd->names)
		ft_error("Calloc error", 9);
	new_cmd->args_amount = ft_count_args(input);
	if (new_cmd->args_amount == 0)
		return (new_cmd);
	ft_get_args(input, new_cmd->args_amount, &new_cmd->args);
	while (new_cmd->args[++i] != NULL)
		if (is_red(new_cmd->args[i]) != 0)
			ft_new_args(new_cmd, &i);
	new_cmd->next = NULL;
	return (new_cmd);
}

t_cmd	*ft_last_command(t_cmd **cmd)
{
	t_cmd	*temp;

	temp = *cmd;
	while (temp->next)
		temp = temp->next;
	return (temp);
}
