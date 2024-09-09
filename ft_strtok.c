/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:52:46 by smarin-a          #+#    #+#             */
/*   Updated: 2024/09/09 11:54:42 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_check_input(t_mini *mini, char *input)
{
	char	**lines;

	lines = NULL;
	mini->flags->locate_red = ft_count_redirect(mini, input, 0);
	mini->flags->quote = ft_check_quote(input, 2, 2, mini);
	mini->flags->pipe = ft_count_pipes(input);
	if (ft_minus_one(mini) == -1)
		return (NULL);
	if (mini->flags->pipe > 0)
	{
		lines = ft_split_pipe(input, '|');
		if (*(lines) == NULL)
			return (NULL);
	}
	return (lines);
}

int	ft_minus_one(t_mini *mini)
{
	if (mini->flags->pipe == -1 || mini->flags->quote == -1
		|| mini->flags->locate_red == -1)
		return (-1);
	return (0);
}

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

int	ft_do_comm(t_cmd *cmd, t_mini *mini)
{
	t_cmd	*current;

	if (cmd == NULL)
	{
		printf(B_RD_0 "No command structure.\n" RESET);
		return (0);
	}
	current = cmd;
	mini->index = 0;
	mini->fd_tmp = 0;
	mini->num_comm = mini->flags->pipe + 1;
	mini->proc = ft_calloc(sizeof(pid_t), mini->num_comm + 1);
	while (current != NULL)
	{
		ft_start_val(current);
		ft_comm(current, mini);
		mini->num_comm--;
		current = current->next;
	}
	ft_wait_bonus(mini);
	return (1);
}

int	ft_strtok(t_mini *mini, t_cmd **cmd, char *input)
{
	char	**lines;
	int		comm;

	lines = ft_check_input(mini, input);
	if (ft_minus_one(mini) == -1)
		return (0);
	if (ft_order_all(mini, cmd, lines, input) == -1)
		return (0);
	print_cmd(*cmd);
	comm = ft_do_comm(*cmd, mini);
	if (comm != 1)
		return (0);
	return (1);
}
