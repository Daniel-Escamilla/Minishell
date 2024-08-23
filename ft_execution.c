/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:25:25 by user              #+#    #+#             */
/*   Updated: 2024/08/23 12:49:59 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *str, int i)
{
	perror(str);
	exit(i);
}

int	ft_more(t_cmd *cmd, int i, int type)
{
	int	j;

	j = 0;
	while (cmd->files->order[i] != NULL)
	{
		if (ft_atoi(cmd->files->order[i]) == type)
			j++;
		i++;
	}
	if (j == 1)
		return (j);
	return (0);
}

int	ft_pick_infile(t_cmd *cmd)
{
	int	i;
	int	fd;
	char	*join;

	i = 0;
	if (cmd->type->infile == 1 && cmd->files->order[i] != NULL)
	{
		while (ft_atoi(cmd->files->order[i]) == 1)
		{
			fd = open(cmd->files->f_order[i], O_RDONLY);
			if (fd == -1)
			{
				join = ft_strjoin("mini: ", cmd->files->f_order[i]);	
				perror(join);
				free(join);
				return (-1);
			}
			if (ft_more(cmd, i, 1) == 1)
				return (fd);
			close(fd);
			i++;
		}
	}
	i = 0;
	if (cmd->type->here_doc == 1 && cmd->files->order[i] != NULL)
	{
		while (ft_atoi(cmd->files->order[i]) == 3)
		{
			fd = open(cmd->files->f_order[i], O_RDONLY);
			if (fd == -1)
			{
				join = ft_strjoin("mini: ", cmd->files->f_order[i]);	
				perror(join);
				free(join);
				return (-1);
			}
			if (ft_more(cmd, i, 3) == 1)
				return (fd);
			close(fd);
			i++;
		}
	}
	return (-1);
}


int	ft_pick_outfile(t_cmd *cmd)
{
	int	i;
	int	fd;
	char	*join;

	i = 0;
	fd = 0;
	while (cmd->files->order[i] != NULL)
	{
		if (ft_atoi(cmd->files->order[i]) == 2)
		{
			fd = open(cmd->files->f_order[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				join = ft_strjoin("mini: ", cmd->files->f_order[i]);	
				perror(join);
				free(join);
			}
			if (ft_more(cmd, i, 2) == 1 && ft_more(cmd, i, 4) == 0)
				return (fd);
			close (fd);
		}
		if (ft_atoi(cmd->files->order[i]) == 4)
		{
			fd = open(cmd->files->f_order[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
			{
				join = ft_strjoin("mini: ", cmd->files->f_order[i]);	
				perror(join);
				free(join);
			}
			if (ft_more(cmd, i, 4) == 1 && ft_more(cmd, i, 2) == 0)
				return (fd);
			close (fd);
		}
		i++;
	}
	// while (cmd->files->order[++i] != NULL)
	// {
	// 	if (cmd->type->outfile == 1 && ft_atoi(cmd->files->order[i]) == 2)
	// 		fd = open(cmd->files->f_order[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// 	else if (cmd->type->append == 1 && ft_atoi(cmd->files->order[i]) == 4)
	// 		fd = open(cmd->files->f_order[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
	// 	if (fd == -1)
	// 	{
	// 		join = ft_strjoin("mini: ", cmd->files->f_order[i]);	
	// 		perror(join);
	// 		free(join);
	// 	}
	// 	if ((cmd->type->outfile == 1 && ft_more(cmd, i, 2) == 1)
	// 		&& (cmd->type->append == 1 && ft_more(cmd, i, 4) == 1))
	// 		return (fd);
	// 	if (fd != 1)
	// 		close (fd);
	// }
	// return (-1);
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
		return (ft_pick_outfile(cmd));
	else if (mini->num_comm == 1)
		return (STDOUT_FILENO);
	return (cmd->names->fd_pipe[1]);
}

void ft_close_fd(t_mini *mini, t_cmd *cmd, int who)
{
	if (who == 'H')
		close(cmd->names->fd_pipe[0]);
	else if (who == 'P')
	{
		close(cmd->names->fd_pipe[1]);
		if (mini->fd_tmp != 0)
			close(mini->fd_tmp);
		if (mini->num_comm != 1)
			mini->fd_tmp = cmd->names->fd_pipe[0];
		else
			close(cmd->names->fd_pipe[0]);
	}
	if (cmd->names->fd_infile != 0)
		close(cmd->names->fd_infile);
	if (cmd->names->fd_outfile != 1)
		close(cmd->names->fd_outfile);
}

void	ft_open_fd(t_cmd *cmd, t_mini *mini)
{
	cmd->names->fd_infile = ft_choose_infile(cmd, mini);
	if (cmd->names->fd_infile == -1)
		return ;
	cmd->names->fd_outfile = ft_choose_outfile(cmd, mini);
	if (cmd->names->fd_outfile == -1)
	{
		if (mini->fd_tmp)
			close(mini->fd_tmp);
		perror("mini: error open outfile");
	}
}

void	ft_comm(t_cmd *cmd, t_mini *mini)
{
	if (mini->num_comm != 0)
	{
		if (pipe(cmd->names->fd_pipe) == -1)
			perror("Pipe Error");
	}
	ft_open_fd(cmd, mini);
	if (cmd->names->fd_infile != -1 && cmd->names->fd_outfile != -1)
	{
		cmd->names->proc[cmd->names->index] = fork();
		if (cmd->names->proc[cmd->names->index] == -1)
			perror("Failed in Fork()");
		if (cmd->names->proc[cmd->names->index] == 0)
		{
			dup2(cmd->names->fd_infile, STDIN_FILENO);
			dup2(cmd->names->fd_outfile, STDOUT_FILENO);
			ft_close_fd(mini, cmd, 'H');
			execve(cmd->cmd, cmd->args, mini->env->env);
			perror("Execve Error");
		}
		ft_close_fd(mini, cmd, 'P');
	}
	cmd->names->index++;
}

