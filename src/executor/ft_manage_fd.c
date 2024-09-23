/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:25:25 by user              #+#    #+#             */
/*   Updated: 2024/09/21 12:27:27 by descamil         ###   ########.fr       */
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
	mini->fd_tmp = mini->fd_pipe[0];
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
		if (mini->fd_pipe[0] > 0 && mini->fd_pipe[0] != STDIN_FILENO)
		{
			close(mini->fd_pipe[0]);
			mini->fd_pipe[0] = STDIN_FILENO;
		}
	}
	else if (who == 'P')
	{
		if (mini->fd_pipe[1] > 0 && mini->fd_pipe[1] != STDOUT_FILENO)
			safe_close(&mini->fd_pipe[1]);
		if (mini->fd_pipe[0] > 0 && mini->fd_pipe[0] != STDIN_FILENO
			&& mini->fd_pipe[0] != mini->fd_tmp)
			safe_close(&mini->fd_pipe[0]);
		if (mini->fd_tmp != 0 && mini->fd_tmp != -1)
		{
			safe_close(&mini->fd_tmp);
			if (mini->num_comm != 0)
				mini->fd_tmp = mini->fd_pipe[0];
		}
		if (mini->num_comm == 0 && mini->fd_tmp > 0)
			safe_close(&mini->fd_tmp);
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
