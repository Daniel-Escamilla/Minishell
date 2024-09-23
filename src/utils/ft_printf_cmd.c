/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:23:41 by descamil          #+#    #+#             */
/*   Updated: 2024/09/21 12:27:27 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

static void	print_cmd_header_and_args(t_cmd *cmd, int *cmd_index)
{
	int	i;

	if (cmd == NULL)
	{
		printf(B_RD_0 "No command structure.\n" RESET);
		return ;
	}
	printf(B_CY_0 "\nCommand structure {-%d-}:\n" RESET, *cmd_index);
	if (cmd->cmd)
		printf(B_OR_0 "  Cmd: {%s}\n" RESET, cmd->cmd);
	else
		printf(B_RD_0 "  Cmd: (null)\n" RESET);
	if (cmd->args)
	{
		printf(B_PR_0 "  Args:\n" RESET);
		i = -1;
		while (cmd->args[++i] != NULL)
			printf(B_GR_0 "   - Args[%d]: {%s}\n" RESET, i, cmd->args[i]);
	}
	else
		printf(B_RD_0 "    Args: (null)\n" RESET);
}

static void	print_cmd_files(t_cmd *cmd)
{
	int	i;

	if (!cmd->files)
	{
		printf(B_RD_0 "  Files: (null)\n" RESET);
		return ;
	}
	printf(B_PR_0"  Files:\n" RESET);
	if (cmd->files->f_order)
	{
		i = -1;
		while (cmd->files->f_order[++i] != NULL)
			printf(B_GR_0 "   - Files[%d]: {%s}\n"RESET,
				i, cmd->files->f_order[i]);
	}
	else
		printf(B_RD_0 "    Files: (null)\n" RESET);
}

static void	print_cmd_order(t_cmd *cmd)
{
	int	i;

	if (cmd->files && cmd->files->order)
	{
		i = -1;
		while (cmd->files->order[++i] != NULL)
			printf(B_GR_0 "   - Order[%d]: {%s}\n" RESET,
				i, cmd->files->order[i]);
	}
	if (cmd->files)
		printf(B_GR_0 "\n   - Error: %d\n" RESET, cmd->files->error);
}

static void	print_cmd_type(t_cmd *cmd)
{
	if (!cmd->type)
	{
		printf(B_RD_0 "  Type: (null)\n" RESET);
		return ;
	}
	printf(B_PR_0 "  Type:\n" RESET);
	printf(B_GR_0 "   - Infile: %d\n" RESET, cmd->type->infile);
	printf(B_GR_0 "   - Outfile: %d\n" RESET, cmd->type->outfile);
	printf(B_GR_0 "   - Here_doc: %d\n" RESET, cmd->type->here_doc);
	printf(B_GR_0 "   - Append: %d\n" RESET, cmd->type->append);
	if (cmd->type->in)
		printf(B_GR_0 "   - In: %s\n" RESET, cmd->type->in);
	else
		printf(B_RD_0 "     In: (null)\n" RESET);
	if (cmd->type->out)
		printf(B_GR_0 "   - Out: %s\n" RESET, cmd->type->out);
	else
		printf(B_RD_0 "     Out: (null)\n" RESET);
}

void	print_cmd(t_cmd *cmd)
{
	t_cmd	*current;
	int		cmd_index;

	current = cmd;
	cmd_index = 0;
	while (current != NULL)
	{
		print_cmd_header_and_args(current, &cmd_index);
		print_cmd_files(current);
		print_cmd_order(current);
		print_cmd_type(current);
		printf("\n");
		current = current->next;
		cmd_index++;
	}
}
