/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:23:41 by descamil          #+#    #+#             */
/*   Updated: 2024/07/12 09:57:09 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_cmd(t_cmd *cmd) {
    if (cmd == NULL) {
        printf(B_RD_0 "No command structure.\n" RESET);
        return;
    }
    t_cmd *current = cmd;
    int cmd_index = 0;
    while (current != NULL) {
        printf(B_CY_0 "\nCommand structure {-%d-}:\n" RESET, cmd_index);
        if (current->cmd)
            printf(B_OR_0 "  Cmd: {%s}\n" RESET, current->cmd);
        else
            printf(B_RD_0 "  Cmd: (null)\n" RESET);
        if (current->args) {
            printf(B_PR_0 "  Args:\n" RESET);
            for (int i = 0; current->args[i] != NULL; i++)
                printf(B_GR_0 "   - Args[%d]: {%s}\n" RESET, i, current->args[i]);
        }
        else
            printf(B_RD_0 "    Args: (null)\n" RESET);

        if (current->files) {
            printf(B_PR_0"  Files:\n" RESET);
            if (current->files->f_order) {
                for (int i = 0; current->files->f_order[i] != NULL; i++)
                    printf(B_GR_0 "   - Files[%d]: {%s}\n" RESET, i, current->files->f_order[i]);
            }
            else
                printf(B_RD_0 "    Files: (null)\n" RESET);
            if (current->files->order) {
                for (int i = 0; current->files->order[i] != NULL; i++)
                    printf(B_GR_0 "   - Order[%d]: {%s}\n" RESET, i, current->files->order[i]);
            }
            printf(B_GR_0 "    Error: %d\n" RESET, current->files->error);
        } else {
            printf(B_RD_0 "  Files: (null)\n" RESET);
        }

        current = current->next;
        cmd_index++;
    }
}
