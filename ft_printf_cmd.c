/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:23:41 by descamil          #+#    #+#             */
/*   Updated: 2024/09/03 12:02:44 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
