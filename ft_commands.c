/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:31:25 by smarin-a          #+#    #+#             */
/*   Updated: 2024/08/17 17:28:09 by user             ###   ########.fr       */
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

char	*ft_get_command(char *input)
{
	int		i;
	int		init;
	char	*command;

	i = 0;
	while (input[i] == 32 || (input[i] == 9 && input[i] <= 13))
		i++;
	init = i;
	while (input[i] && input[i] != 32 && !(input[i] >= 9
			&& input[i] <= 13) && !ft_is_not_mayor_n_minor_char(input[i]))
	{
		if (input[i] == 34 || input[i] == 39)
			i = ft_locate_next_quote(i + 1, input, input[i]);
		i++;
	}
	if (i && !ft_is_not_mayor_n_minor_char(input[i]))
	{
		command = ft_substr(input, init, i);
		if (command == NULL)
			ft_exit_error(NULL, "Malloc error", 50);
	}
	return (command);
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

void	ft_free_fcheck_args(char **args1, char **args2)
{
	if (args1)
		ft_strstr_free(args1);
	ft_strstr_free(args2);
}

char	**ft_new_args(char **args, int pos, int i, int j)
{
	char	**args1;
	char	**args2;
	char	**tmp;

	args1 = NULL;
	if (pos != 0)
		args1 = ft_calloc(sizeof(char *), pos + 1);
	while (i != pos)
		args1[j++] = ft_strdup(args[i++]);
	if (i == pos)
		args2 = ft_split_red(args[pos], 0);
	if (args1 != NULL)
		tmp = ft_strstr_join(args1, args2);
	else
		tmp = ft_strstr_join(args2, NULL);
	ft_free_fcheck_args(args1, args2);
	args1 = NULL;
	if (ft_strstr_len(args) - pos != 1)
		args1 = ft_calloc(sizeof(char *), ft_strstr_len(args) - pos);
	j = 0;
	while (ft_strstr_len(args) - pos > 1 && args[++i])
		args1[j++] = ft_strdup(args[i]);
	args2 = ft_strstr_join(tmp, args1);
	ft_free_fcheck_args(args1, tmp);
	return (args2);
}

t_cmd	*ft_add_command(char *input, int i)
{
	t_cmd	*new_cmd;
	char	**args;

	new_cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!new_cmd)
		ft_exit_error(NULL, "Calloc error", 9);
	new_cmd->names = ft_calloc(sizeof(t_names), 1);
	if (!new_cmd->names)
		ft_exit_error(NULL, "Calloc error", 9);
	new_cmd->args_amount = ft_count_args(input);
	if (new_cmd->args_amount == 0)
		return (new_cmd);
	ft_get_args(input, new_cmd->args_amount, &new_cmd->args);
	while (new_cmd->args[++i] != NULL)
	{
		if (is_red(new_cmd->args[i]) != 0)
		{
			args = ft_new_args(new_cmd->args, i, 0, 0);
			if (ft_strstr_len(args) - ft_strstr_len(new_cmd->args) != 0)
				i = ft_strstr_len(args) - ft_strstr_len(new_cmd->args) - 1;
			if (new_cmd->args)
				ft_strstr_free(new_cmd->args);
			new_cmd->args = ft_strstr_join(args, NULL);
			ft_strstr_free(args);
		}
	}
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
