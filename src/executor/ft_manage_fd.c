/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:25:25 by user              #+#    #+#             */
/*   Updated: 2024/11/27 16:44:30 by descamil         ###   ########.fr       */
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

void	ft_close_and_update_fds(t_mini *mini, t_cmd *cmd, char who)
{
	if (who == 'H')
	{
		close(mini->fd_pipe[0]);
		close(mini->fd_pipe[1]);
	}
	else if (who == 'P')
	{
		close(mini->fd_pipe[1]);
		if (mini->num_comm == 1)
		{
			close(mini->fd_pipe[0]);
			safe_close(&mini->fd_tmp);
		}
		else
		{
			safe_close(&mini->fd_tmp);
			mini->fd_tmp = mini->fd_pipe[0];
		}
		if (cmd->names->fd_infile != mini->fd_tmp)
			safe_close(&cmd->names->fd_infile);
		safe_close(&cmd->names->fd_outfile);
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
