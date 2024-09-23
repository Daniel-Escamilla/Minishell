/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:25:25 by user              #+#    #+#             */
/*   Updated: 2024/09/23 23:29:46 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

int	ft_choose_infile(t_cmd *cmd, t_mini *mini)
{
	if (cmd->type && cmd->type->in
		&& (cmd->type->infile == 1 || cmd->type->here_doc == 1))
		return (ft_pick_infile(cmd, mini));
	else if (mini->fd_tmp != -1)
		return (mini->fd_tmp);
	return (STDIN_FILENO);
}

int	ft_choose_outfile(t_cmd *cmd, t_mini *mini)
{
	if (cmd->type && cmd->type->out && (cmd->type->outfile == 1
			|| cmd->type->append == 1))
		return (ft_pick_outfile(cmd, mini));
	else if (mini->num_comm == 1)
		return (STDOUT_FILENO);
	return (mini->fd_pipe[1]);
}

void	ft_close_and_update_fds(t_mini *mini, char who)
{
	if (who == 'H')
	{
		close(mini->fd_pipe[0]);
		close(mini->fd_pipe[1]);
	}
	else if (who == 'P')
	{
		close(mini->fd_pipe[1]); // Cerrar el extremo de escritura del pipe

		// Si es el último comando
		if (mini->num_comm == 0)
		{
			close(mini->fd_pipe[0]);
			close(mini->fd_tmp);
		}
		else
		{
			if (mini->fd_tmp > 2) // Cerrar fd_tmp si tiene un valor previo válido
			{
				close(mini->fd_tmp); // Cerrar fd_tmp
			}
			mini->fd_tmp = mini->fd_pipe[0]; // Guardar fd_pipe[0] para uso futuro
		}
	}

}


void	ft_open_fd(t_cmd *cmd, t_mini *mini)
{
	cmd->names->fd_infile = ft_choose_infile(cmd, mini);
	if (cmd->names->fd_infile == -1)
		return ;
	cmd->names->fd_outfile = ft_choose_outfile(cmd, mini);
	if (cmd->names->fd_outfile == -1)
		return ;
}
