/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_comm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:52:46 by smarin-a          #+#    #+#             */
/*   Updated: 2025/02/27 12:56:06 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static void	ft_handle_export_quotes(t_cmd *cmd, int i)
{
	char	*itoa;
	char	**tmp;

	itoa = ft_itoa(i);
	if (cmd->export_quotes == NULL)
		cmd->export_quotes = ft_sindub_join(NULL, itoa);
	else
	{
		tmp = ft_strstr_dup(cmd->export_quotes);
		ft_strstr_free(cmd->export_quotes);
		cmd->export_quotes = ft_sindub_join(tmp, itoa);
		ft_strstr_free(tmp);
	}
	free(itoa);
}

int ft_is_quote(char *str, int i)
{
	if (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
	}
	return (0);
}

static void	ft_quotes_var_expander(t_mini *mini, t_cmd *cmd)
{
	char	*str;
	int		i;

	i = 0;
	if (mini->flags->pipe != 0)
		return ;
	if (ft_strncmp(cmd->args[0], "export", 6) == 0 && ft_strlen(cmd->args[0]) == 6)
	{
		cmd->export_quotes = NULL;
		while (cmd->args[i])
		{
			str = ft_strchr(cmd->args[i], '=');
			if (str && str[0] && str[0] == '\0')
				return ;
			if (ft_is_quote(str, 1) == 1 && ft_is_quote(str, 2) == 1)
				ft_handle_export_quotes(cmd, i);
			else
				ft_handle_export_quotes(cmd, 0);
			i++;
		}
		printf("EXPORT\n");
	}
}

int	ft_order_all(t_mini *mini, t_cmd **cmd, char **lines, char *input)
{
	if (mini->flags->pipe == 0)
	{
		*(cmd) = ft_add_command(input, -1);
		ft_move_files(*(cmd), mini);
	}
	else
		process_lines(cmd, mini, lines, 0);
	if (mini->error == -2)
		return (-1);
	ft_quotes_var_expander(mini, *cmd);
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

static void	ft_start_comm_val(t_mini *mini)
{
	mini->index = 0;
	mini->fd_tmp = -1;
	mini->num_comm = mini->flags->pipe + 1;
	mini->proc = ft_calloc(sizeof(pid_t), (size_t)mini->num_comm + 1);
	if (mini->num_comm == 1)
		mini->single = 1;
}

int	ft_do_comm(t_cmd *cmd, t_mini *mini)
{
	t_cmd	*current;

	current = cmd;
	ft_start_comm_val(mini);
	ft_fill_fd(mini, cmd);
	if (ft_here_doc(mini, cmd, mini->env->env) == 1)
		return (0);
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
