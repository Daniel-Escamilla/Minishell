/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_comm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarin-a <smarin-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:12:19 by descamil          #+#    #+#             */
/*   Updated: 2025/03/05 11:23:55 by smarin-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static void	ft_update_underline(t_mini *mini, t_cmd **cmd)
{
	char	*variable;
	int		i;

	i = 0;
	if (mini->flags->pipe != 0)
		return ;
	if (ft_strstr_len((*cmd)->args) == 0)
		return ;
	variable = ft_strdup((*cmd)->args[ft_strstr_len((*cmd)->args) - 1]);
	if (ft_strncmp(variable, "env", 3) == 0)
	{
		free(variable);
		variable = ft_strdup("/usr/bin/env");
	}
	while (mini->env->env && mini->env->env[i])
	{
		if (ft_strncmp(mini->env->env[i], "_=", 2) == 0)
		{
			ft_remove_var(&mini->env->env, i);
			ft_add_var(&mini->env->env, "_=", variable);
			free(variable);
			return ;
		}
		i++;
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
	ft_update_underline(mini, cmd);
	return (0);
}

int	ft_do_comm(t_cmd *cmd, t_mini *mini)
{
	t_cmd	*current;

	current = cmd;
	ft_start_comm_val(mini);
	ft_fill_fd(mini, cmd);
	if (ft_here_doc(mini, cmd) == 1)
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
