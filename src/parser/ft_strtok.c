/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:52:46 by smarin-a          #+#    #+#             */
/*   Updated: 2024/10/24 10:54:21 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static void	ft_handle_quote_args(t_cmd *cmd, int i)
{
	char	*itoa;
	char	**tmp;

	itoa = ft_itoa(i);
	if (cmd->quote_args == NULL)
		cmd->quote_args = ft_sindub_join(NULL, itoa);
	else
	{
		tmp = ft_strstr_dup(cmd->quote_args);
		ft_strstr_free(cmd->quote_args);
		cmd->quote_args = ft_sindub_join(tmp, itoa);
		ft_strstr_free(tmp);
	}
	free(itoa);
}

static void	ft_do_remove_args_quotes(t_cmd *cmd)
{
	int		*quotes;
	int		i = 0;

	while (cmd->args && cmd->args[i])
	{
		quotes = ft_find_quotes(cmd->args[i], 0);
		if (quotes[1] != -1)
			ft_handle_quote_args(cmd, i);
		if (quotes[0] != -1 && quotes[1] != -1)
			ft_rm_quotes(&cmd->args[i], quotes);
		else
			free(quotes);
		i++;
	}
}

static void	ft_do_remove_files_quotes(t_cmd *cmd)
{
	int		*quotes;
	int		i = 0;

	while (cmd->files && cmd->files->f_order && cmd->files->f_order[i])
	{
		if (ft_atoi(cmd->files->order[i]) != 3)
		{
			quotes = ft_find_quotes(cmd->files->f_order[i], 0);
			ft_rm_quotes(&cmd->files->f_order[i], quotes);
			free(quotes);
		}
		i++;
	}
}

static void	ft_do_remove_quotes(t_cmd *cmd)
{
	t_cmd	*current = cmd;

	while (current != NULL)
	{
		ft_do_remove_args_quotes(current);
		ft_do_remove_files_quotes(current);
		current = current->next;
	}
}

static void	ft_split_space_join(char ***result, char *tmp)
{
	char	**copy;
	char	**str;

	str = ft_split(tmp, ' ');
	if (*result == NULL)
		*result = ft_strstr_join(str, NULL);
	else
	{
		copy = ft_strstr_join(*result, str);
		ft_strstr_free(*result);
		*result = copy;
	}
	ft_strstr_free(str);
}

static void ft_quit_spaces(t_cmd **cmd)
{
	char	**result;
	char	**copy;
	char	**tmp;
	int		i;

	i = -1;
	result = NULL;
	tmp = ft_strstr_dup((*cmd)->args);
	while (tmp[++i])
	{
		if (ft_has_quotes(tmp[i], 0) == 0 && ft_strchr(tmp[i], ' '))
			ft_split_space_join(&result, tmp[i]);
		else
		{
			copy = ft_sindub_join(result, tmp[i]);
			ft_strstr_free(result);
			result = copy;
		}
	}
	ft_strstr_free(tmp);
	ft_strstr_free((*cmd)->args);
	(*cmd)->args = result;
}

static int	ft_order_all(t_mini *mini, t_cmd **cmd, char **lines, char *input)
{
	if (mini->flags->pipe == 0)
	{
		*(cmd) = ft_add_command(input, -1);
		ft_move_files(*(cmd), mini);
	}
	else
		process_lines(cmd, mini, lines, 0);
	ft_do_expander(mini, *cmd);
	ft_strstr_free(lines);
	if (mini->cmd->files->error == -1)
		return (-1);
	ft_quit_spaces(cmd);
	ft_do_remove_quotes(*cmd);
	
	ft_remove_files(*cmd, mini);
	if (mini->cmd->files->error == -1)
		return (-1);
	ft_select_files(*cmd, 0);
	print_cmd(*cmd);
	return (0);
}

static void	ft_fill_fd(t_mini *mini, t_cmd *cmd)
{
	t_cmd	*current;
	int		fd;
	int		i;

	fd = -1;
	current = cmd;
	while (current != NULL)
	{
		i = 0;
		while (cmd->files->order && cmd->files->order[i] != NULL)
		{
			cmd->error = 2;
			if (ft_atoi(cmd->files->order[i]) == 2)
				fd = ft_handle_trunc(cmd, mini, i);
			else if (ft_atoi(cmd->files->order[i]) == 4)
				fd = ft_handle_append(cmd, mini, i);
			cmd->error = 0;
			i++;
			safe_close(&fd);
		}
		current = current->next;
	}
}

static int	ft_do_comm(t_cmd *cmd, t_mini *mini)
{
	t_cmd	*current;

	current = cmd;
	mini->index = 0;
	mini->fd_tmp = -1;
	mini->num_comm = mini->flags->pipe + 1;
	mini->proc = ft_calloc(sizeof(pid_t), (size_t)mini->num_comm + 1);
	if (mini->num_comm == 1)
		mini->single = 1;
	ft_fill_fd(mini, cmd);
	while (current != NULL)
	{
		ft_start_val(current);
		ft_comm(current, mini);
		mini->index++;
		mini->num_comm--;
		current = current->next;
	}
	ft_wait_bonus(mini);
	return (0);
}

int	ft_strtok(t_mini *mini, t_cmd **cmd, char *input)
{
	char	**lines;

	mini->error = 0;
	lines = ft_check_input(mini, input);
	if (ft_error_rqp(mini, input) == 1)
		return (-1);
	if (ft_order_all(mini, cmd, lines, input) == -1)
		return (-1);
	if (ft_do_comm(*cmd, mini) == -1)
		return (-1);
	return (0);
}
