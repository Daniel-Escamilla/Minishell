/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:52:46 by smarin-a          #+#    #+#             */
/*   Updated: 2024/10/22 19:24:36 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static void	ft_do_remove_quotes(t_cmd *cmd)
{
	t_cmd	*current;
	int		*quotes;
	char	*itoa;
	char	**tmp;
	int		i;

	i = 0;
	current = cmd;
	while (current != NULL)
	{
		while (current->args && current->args[i])
		{
			quotes = ft_find_quotes(current->args[i], 0);
			if (quotes[1] != -1 && cmd->quote_args == NULL)
			{
				itoa = ft_itoa(i);
				cmd->quote_args = ft_sindub_join(NULL, itoa);
				free(itoa);
			}
			else if (quotes[1] != -1)
			{
				itoa = ft_itoa(i);
				tmp = ft_strstr_dup(cmd->quote_args);
				ft_strstr_free(cmd->quote_args);
				cmd->quote_args = ft_sindub_join(tmp, itoa);
				free(itoa);
				ft_strstr_free(tmp);
			}
			if (quotes[0] != -1 && quotes[1] != -1)
				ft_rm_quotes(&current->args[i], quotes);
			else
				free(quotes);
			i++;
		}
		i = 0;
		while (current->files && current->files->f_order
			&& current->files->f_order[i])
		{
			if (ft_atoi(current->files->order[i]) == 3)
				i++;
			else if (current->files->f_order[i])
			{
				quotes = ft_find_quotes(current->files->f_order[i], 0);
				ft_rm_quotes(&current->files->f_order[i++], quotes);
				free(quotes);
			}
		}
		current = current->next;
	}
}

static char **ft_update_args(char **tmp, char **str, int i, int size)
{
	char	**tmp2;
	int		j;
	int		k;
	int		l;

	j = 0;
	k = 0;
	l = 0;
	tmp2 = ft_calloc(sizeof(char *), size + 1);
	if (!tmp2)
		return NULL;
	while (j < i)
		tmp2[j++] = ft_strdup(tmp[l++]);
	while (str[k])
		tmp2[j++] = ft_strdup(str[k++]);
	while (tmp[l + 1])
		tmp2[j++] = ft_strdup(tmp[++l]);
	return (tmp2);
}

static char **ft_process_arg(char **tmp, int i, int *size)
{
	char	**str;
	char	**tmp2;
	int		new_size;
	
	str = ft_split(tmp[i], ' ');
	if (!str)
		return (NULL);
	ft_strstr_printf(str);
	new_size = *size + ft_strstr_len(str) - 1;
	tmp2 = ft_update_args(tmp, str, i, new_size);
	ft_strstr_free(str);
	return (tmp2);
}

static void ft_quit_spaces(t_cmd **cmd)
{
	char	**tmp2;
	char	**tmp;
	int		size;
	int		i;

	i = 0;
	tmp = ft_strstr_dup((*cmd)->args);
	size = ft_strstr_len(tmp);
	while (tmp[i])
	{
		if (ft_has_quotes(tmp[i], 0) == 0 && ft_strchr(tmp[i], ' '))
		{
			tmp2 = ft_process_arg(tmp, i, &size);
			ft_strstr_free(tmp);
			if (!tmp2)
				return ;
			tmp = ft_strstr_dup(tmp2);
			i += ft_strstr_len(tmp2) - 1;
			ft_strstr_free(tmp2);
			tmp2 = NULL;
			printf("I --> %d\n", i);
		}
		i++;
	}
	if (ft_strstr_len(tmp) > size)
	{
		ft_strstr_free((*cmd)->args);
		(*cmd)->args = ft_strstr_dup(tmp2);
		ft_strstr_free(tmp2);
	}
	ft_strstr_free(tmp);
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
	print_cmd(*cmd);
	ft_do_remove_quotes(*cmd);
	
	ft_remove_files(*cmd, mini);
	if (mini->cmd->files->error == -1)
		return (-1);
	ft_select_files(*cmd, 0);
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
