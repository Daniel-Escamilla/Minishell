/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:52:46 by smarin-a          #+#    #+#             */
/*   Updated: 2024/09/17 16:33:06 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ft_rm_quotes(mini, *cmd);
int	ft_order_all(t_mini *mini, t_cmd **cmd, char **lines, char *input)
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
	ft_remove_files(*cmd, mini);
	if (mini->cmd->files->error == -1)
		return (-1);
	ft_select_files(*cmd, 0);
	return (0);
}

void	ft_fill_fd(t_mini *mini, t_cmd *cmd)
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
			if (cmd->error == 2)
				cmd->error = 0;
			i++;
			if (fd != -1)
				close(fd);
		}
		current = current->next;
	}
}

int	ft_do_comm(t_cmd *cmd, t_mini *mini)
{
	t_cmd	*current;

	if (cmd == NULL)
	{
		printf(B_RD_0 "No command structure.\n" RESET);
		return (1);
	}
	current = cmd;
	ft_start_comm_val(&mini);
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
	if (ft_minus_one(mini) == -1)
		return (-1);
	if (ft_order_all(mini, cmd, lines, input) == -1)
		return (-1);
	if (ft_do_comm(*cmd, mini) == -1)
		return (-1);
	print_cmd(*cmd);
	return (0);
}
