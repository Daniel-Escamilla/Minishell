/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:52:46 by smarin-a          #+#    #+#             */
/*   Updated: 2024/10/05 13:10:44 by descamil         ###   ########.fr       */
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
				cmd->quote_args = ft_sindub_join(NULL, ft_itoa(i));
			else if (quotes[1] != -1)
			{
				itoa = ft_itoa(i);
				tmp = ft_strstr_dup(cmd->quote_args);
				ft_strstr_free(cmd->quote_args);
				cmd->quote_args = ft_sindub_join(tmp, itoa);
				free(itoa);
			}
			ft_rm_quotes(&current->args[i++], quotes);
			free(quotes);
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
	// printf("%d\n", mini->num_comm);
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
	// if (cmd->built == 1)
	// 	printf("%s\n", get_next_line(mini->fd_pipe[0]));
	return (0);
}

int	ft_strtok(t_mini *mini, t_cmd **cmd, char *input)
{
	char	**lines;

	mini->error = 0;
	lines = ft_check_input(mini, input);
	if (mini->flags->pipe == -1 || mini->flags->quote == -1
		|| mini->flags->locate_red == -1)
		return (-1);
	if (ft_order_all(mini, cmd, lines, input) == -1)
		return (-1);
	if (ft_do_comm(*cmd, mini) == -1)
		return (-1);
	// print_cmd(*cmd);
	return (0);
}
