/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_comm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:12:19 by descamil          #+#    #+#             */
/*   Updated: 2025/03/05 11:04:05 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

void	print_cmd(t_cmd *cmd)
{
	t_cmd	*current;
	int		cmd_index;
	int		i;

	if (cmd == NULL)
	{
		printf(B_RD_0 "No command structure.\n" RESET);
		return ;
	}
	current = cmd;
	cmd_index = 0;
	while (current != NULL)
	{
		printf(B_CY_0 "\nCommand structure {-%d-}:\n" RESET, cmd_index);
		if (current->cmd)
			printf(B_OR_0 "  Cmd: {%s}\n" RESET, current->cmd);
		else
			printf(B_RD_0 "  Cmd: (null)\n" RESET);
		if (current->args)
		{
			printf(B_PR_0 "  Args:\n" RESET);
			i = -1;
			while (current->args[++i] != NULL)
				printf(B_GR_0 "   - Args[%d]: {%s}\n" RESET,
					i, current->args[i]);
		}
		else
			printf(B_RD_0 "    Args: (null)\n" RESET);
		if (current->files)
		{
			printf(B_PR_0"  Files:\n" RESET);
			if (current->files->f_order)
			{
				i = -1;
				while (current->files->f_order[++i] != NULL)
					printf(B_GR_0 "   - Files[%d]: {%s}\n"RESET,
						i, current->files->f_order[i]);
			}
			else
				printf(B_RD_0 "    Files: (null)\n" RESET);
			if (current->files->order)
			{
				i = -1;
				while (current->files->order[++i] != NULL)
					printf(B_GR_0 "   - Order[%d]: {%s}\n" RESET,
						i, current->files->order[i]);
			}
			printf(B_GR_0 "\n   - Error: %d\n" RESET, current->files->error);
		}
		else
			printf(B_RD_0 "  Files: (null)\n" RESET);
		if (current->type)
		{
			printf(B_PR_0 "  Type:\n" RESET);
			printf(B_GR_0 "   - Infile: %d\n" RESET, current->type->infile);
			printf(B_GR_0 "   - Outfile: %d\n" RESET, current->type->outfile);
			printf(B_GR_0 "   - Here_doc: %d\n" RESET, current->type->here_doc);
			printf(B_GR_0 "   - Append: %d\n" RESET, current->type->append);
			if (current->type->in)
				printf(B_GR_0 "   - In: %s\n" RESET, current->type->in);
			else
				printf(B_RD_0 "     In: (null)\n" RESET);
			if (current->type->out)
				printf(B_GR_0 "   - Out: %s\n" RESET, current->type->out);
			else
				printf(B_RD_0 "     Out: (null)\n" RESET);
		}
		else
			printf(B_RD_0 "  Type: (null)\n" RESET);
		current = current->next;
		cmd_index++;
	}
}

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
	print_cmd(*cmd);
	ft_quotes_var_expander(mini, *cmd);
	print_cmd(*cmd);
	ft_do_expander(mini, *cmd);
	print_cmd(*cmd);
	ft_strstr_free(lines);
	print_cmd(*cmd);
	if (mini->cmd->files->error == -1)
		return (-1);
	ft_quit_spaces(cmd);
	print_cmd(*cmd);
	ft_do_remove_quotes(*cmd);
	print_cmd(*cmd);
	ft_remove_files(*cmd, mini);
	print_cmd(*cmd);
	if (mini->cmd->files->error == -1)
		return (-1);
	ft_select_files(*cmd, 0);
	print_cmd(*cmd);
	ft_update_underline(mini, cmd);
	print_cmd(*cmd);
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
