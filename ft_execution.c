/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:25:25 by user              #+#    #+#             */
/*   Updated: 2024/08/17 18:31:32 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *str, int i)
{
	perror(str);
	exit(i);
}

int	ft_pick_infile(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->type->infile == 1)
	{
		while (ft_atoi(cmd->files->order[i]) == 1 || i == 0)
		{
			if (access(cmd->files->f_order[i], R_OK) == -1)
				return (-1); // -2
			i++;
		}
		return (open(cmd->type->in, O_RDONLY));
	}
	i = 0;
	if (cmd->type->here_doc == 1)
	{
		while (ft_atoi(cmd->files->order[i]) == 3 || i == 0)
		{
			if (access(cmd->files->f_order[i], R_OK) == -1)
				return (-1); // -2
			i++;
		}
		return (open(cmd->type->in, O_RDONLY));
	}
	return (-1);
}

int	ft_pick_outfile(t_cmd *cmd, t_mini *mini)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	while (cmd->type->outfile == 1)
	{
		if (ft_atoi(cmd->files->order[i]) == 2)
		{
			if (mini->flags->redirect->si_ri == 1)
				return (open(cmd->type->out, O_WRONLY | O_CREAT | O_TRUNC, 0644));
			fd = open(cmd->files->f_order[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				ft_error ("Error open outfile", 1);
			close (fd);
			mini->flags->redirect->si_ri--;
		}
		i++;
	}
	while (cmd->type->append == 1)
	{
		if (ft_atoi(cmd->files->order[i]) == 4)
		{
			if (mini->flags->redirect->do_ri == 1)
				return (open(cmd->type->out, O_WRONLY | O_CREAT | O_APPEND, 0644));
			fd = open(cmd->files->f_order[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				ft_error ("Error open outfile", 1);
			close (fd);
			mini->flags->redirect->do_ri--;
		}
		i++;
	}
	return (-1);
}


int	ft_choose_infile(t_cmd *cmd, t_mini *mini)
{
	if (cmd->type && cmd->type->in && (cmd->type->infile == 1 || cmd->type->here_doc == 1))
		return (ft_pick_infile(cmd));
	else if (mini->fd_tmp != -1)
		return (mini->fd_tmp);
	return (STDIN_FILENO);
}

int	ft_choose_outfile(t_cmd *cmd, t_mini *mini)
{
	if (cmd->type && cmd->type->out && (cmd->type->outfile == 1 || cmd->type->append == 1))
		return (ft_pick_outfile(cmd, mini));
	else if (mini->num_comm == 1)
		return (STDOUT_FILENO);
	return (cmd->names->fd_pipe[1]);
}
// Restar [num_comm] para iterar los comandos.
void	ft_comm(t_cmd *cmd, t_mini *mini)
{
	if (pipe(cmd->names->fd_pipe) == -1)
		ft_error("Pipe Error", 1);
	cmd->names->proc[cmd->names->index] = fork();
	if (cmd->names->proc[cmd->names->index] == -1)
		ft_error("Failed in Fork()", 1);
	if (cmd->names->proc[cmd->names->index] == 0)
	{

		
		ft_putstr_fd("Cierra fd_pipe[0] --> ", 2);
		ft_putnbr_fd(cmd->names->fd_pipe[0], 2);
		write(2, "\n", 1);
		close(cmd->names->fd_pipe[0]);



		cmd->names->fd_infile = ft_choose_infile(cmd, mini);

		ft_putnbr_fd(cmd->names->fd_infile, 2);
		write(2, "\n", 1);
		if (cmd->names->fd_infile == -1)
			ft_error("Error open infile", 1);

			

			
		cmd->names->fd_outfile = ft_choose_outfile(cmd, mini);

		if (cmd->names->fd_outfile == -1)
		{
			if (mini->fd_tmp)
				close(mini->fd_tmp);
			ft_error("Error open outfile", 1);
		}
		ft_putstr_fd("Aquí\n", 2);



		
		dup2(cmd->names->fd_infile, STDIN_FILENO);
		
		dup2(cmd->names->fd_outfile, STDOUT_FILENO);

		
		// ft_putnbr_fd(dup2(cmd->names->fd_infile, STDIN_FILENO), 2);
		// write(2, "\n", 1);
		// ft_putnbr_fd(dup2(cmd->names->fd_outfile, STDOUT_FILENO), 2);
		// write(2, "\n", 1);
		if (cmd->names->fd_infile != 0)
			close(cmd->names->fd_infile);
		if (cmd->names->fd_outfile != 1)
			close(cmd->names->fd_outfile);
		execve(cmd->cmd, cmd->args, mini->env->env);
	}
	
	if (mini->num_comm != 1)
		mini->fd_tmp = cmd->names->fd_pipe[0];
	else
		close(cmd->names->fd_pipe[0]);
	cmd->names->index++;
	close(cmd->names->fd_pipe[1]);
}

