/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:25:25 by user              #+#    #+#             */
/*   Updated: 2024/08/29 14:52:11 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_sindub_join(char **str, char *str1)
{
	char	**result;
	int		len;
	int		i;

	i = -1;
	if (str == NULL)
		len = 0;
	else
		len = ft_strstr_len(str);
	result = ft_calloc(sizeof(char *), len + 1 + 1);
	while (++i < len)
		result[i] = ft_strdup(str[i]);
	result[i] = ft_strdup(str1);
	return (result);
}

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

int	ft_pick_infile(t_cmd *cmd/*, t_mini *mini*/)
{
	int		i;
	int		fd;
	char	*join;

	i = 0;
	cmd->names->h_d = 0;
	while (cmd->files->order[i] != NULL)
	{
		if (ft_atoi(cmd->files->order[i]) == 1)
		{
			fd = open(cmd->files->f_order[i], O_RDONLY);
			if (fd == -1)
			{
				join = ft_strjoin("mini: ", cmd->files->f_order[i]);	
				perror(join);
				free(join);
				// mini->error = -2;
				return (-1);
			}
			if (ft_more(cmd, i, 1) == 1)
				return (fd);
			close(fd);
		}
		if (ft_atoi(cmd->files->order[i]) == 3)
		{
			cmd->names->h_d++; // Se van a utilizar para crear los here_doc en los hijos
			if (ft_more(cmd, i, 3) == 1)
				return (-2); // Si sale con -2 el infilie que se coje es un here_doc
		}
		i++;
	}
	return (-1);
}


int	ft_pick_outfile(t_cmd *cmd, t_mini *mini)
{
	int		i;
	int		fd;
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
				mini->error = -2;
				return (-1);
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
				mini->error = -2;
				return (-1);
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
		return (ft_pick_infile(cmd/*, mini*/));
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
	return (mini->fd_pipe[1]);
}

void ft_close_fd(t_mini *mini, int who)
{
	if (who == 'H')
		close(mini->fd_pipe[0]);
	else if (who == 'P')
	{
		close(mini->fd_pipe[1]);
		if (mini->fd_tmp != 0)
			close(mini->fd_tmp);
		if (mini->num_comm != 1)
			mini->fd_tmp = mini->fd_pipe[0];
		else
			close(mini->fd_pipe[0]);
	}
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

void	ft_here_doc(t_cmd *cmd, t_mini *mini)
{
	char	*line;
	int		fd_tmp;
	int		index;
	int		i;

	i = 0;
	while (cmd->names->h_d > 0)
	{
		index = 0;
		if (ft_atoi(cmd->files->order[i]) == 3)
		{
			cmd->names->h_d--;
			cmd->names->join = ft_strdup(".here_doc");
			while (access(cmd->names->join, F_OK) != -1)
			{
				free(cmd->names->join);
				cmd->names->join = ft_strjoin(".here_doc", ft_itoa(index++));
			}
			if (cmd->names->join)
			{
				ft_putstr_fd(cmd->names->join, 2);
				write(2, "\n", 1);
			}
			fd_tmp = open(cmd->names->join, O_WRONLY | O_CREAT, 0666);
			if (fd_tmp == -1)
				ft_error("Error open", 2);
			while (1)
			{
				line = readline("> ");
				if (ft_strnstr(line, cmd->files->f_order[i], ft_strlen(cmd->files->f_order[i])) && ft_strlen(line) == ft_strlen(cmd->files->f_order[i]))
				{
					free(line);
					break;
				}
				if (write(fd_tmp, line, ft_strlen(line)) == -1)
					ft_error("Error write", 2);
				if (write(fd_tmp, "\n", 1) == -1)
					ft_error("Error write", 2);
				free(line);
			}
			close(fd_tmp);
			if (cmd->names->fd_infile == -2) // Es el utimo, por lo que hay que modificar cmd->names->fd_infile;
			{
				cmd->names->fd_infile = open(cmd->names->join, O_RDONLY);
				if (mini->join != NULL)
				{
					char	**tmp = ft_strstr_dup(mini->join);
					ft_strstr_free(mini->join);
					mini->join = ft_sindub_join(tmp, cmd->names->join);
					ft_strstr_free(tmp);
				}
				else
					mini->join = ft_sindub_join(NULL, cmd->names->join);
				// ft_strstr_printf(mini->join);
			}
			else
				unlink(cmd->names->join);
			free(cmd->names->join);
		}
		i++;
	}
	ft_strstr_printf(mini->join);
}

void	ft_comm(t_cmd *cmd, t_mini *mini)
{
	if (mini->num_comm != 0)
	{
		if (pipe(mini->fd_pipe) == -1)
			perror("Pipe Error");
	}
	ft_open_fd(cmd, mini);
	if (cmd->names->fd_infile != -1 && cmd->names->fd_outfile != -1)
	{
		mini->proc[mini->index] = fork();
		if (mini->proc[mini->index] == -1)
			perror("Failed in Fork()");
		if (mini->proc[mini->index] == 0)
		{
			ft_here_doc(cmd, mini);
			ft_putstr_fd("IN --> ", 2);
			ft_putnbr_fd(cmd->names->fd_infile, 2);
			write(2, "\n", 1);
			ft_putstr_fd("OUT --> ", 2);
			ft_putnbr_fd(cmd->names->fd_outfile, 2);
			write(2, "\n", 1);
			dup2(cmd->names->fd_infile, STDIN_FILENO);
			dup2(cmd->names->fd_outfile, STDOUT_FILENO);
			ft_close_fd(mini, 'H');
			ft_putstr_fd(cmd->cmd, 2);
			write(2, "\n", 1);
			if (ft_strnstr(cmd->cmd, "/usr/bin/env", ft_strlen("/usr/bin/env")) != NULL)
				ft_strstr_printf(mini->env->env);
			else
			{
				execve(cmd->cmd, cmd->args, mini->env->env);
				perror("Execve Error");
			}
		}
		ft_close_fd(mini, 'P');
	}
	else
	{
		close(mini->fd_pipe[0]);
		close(mini->fd_pipe[1]);
		if (mini->fd_tmp != 0)
			close(mini->fd_tmp);
	}
	mini->index++;
}
