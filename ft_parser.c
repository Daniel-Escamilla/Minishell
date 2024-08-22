/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:36:51 by user              #+#    #+#             */
/*   Updated: 2024/07/23 14:37:08 by user             ###   ########.fr       */
/*                                                							  */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_str_expander(t_mini *mini, char **args)
{
	char	**tmp;
	char	**result;
	int		size;
	int		i;

	i = -1;
	result = NULL;
	size = ft_strstr_len(args);
	tmp = ft_strstr_dup(args);
	ft_strstr_free(args);
	result = ft_calloc(sizeof(char *), size + 1);
	if (result == NULL)
	{
		ft_strstr_free(tmp);
		return (NULL);
	}
	while (tmp[++i])
		result[i] = ft_expander(mini->env->env, tmp[i]);
	ft_strstr_free(tmp);
	return (result);
}

void	ft_do_expander(t_mini *mini, t_cmd *cmd)
{
	char	**tmp;
	t_cmd	*current;
	int		i;

	i = 0;
	current = cmd;
	while (current != NULL)
	{
		if (current->args)
		{
			tmp = ft_strstr_dup(current->args);
			ft_strstr_free(current->args);
			current->args = NULL;
			current->args = ft_str_expander(mini, tmp);
			// ft_strstr_free(tmp);
			// tmp = NULL;
		}
		if (current->files->f_order)
		{
			tmp = NULL;
			tmp = ft_strstr_dup(current->files->f_order);
			ft_strstr_free(current->files->f_order);
			current->files->f_order = NULL;
			current->files->f_order = ft_str_expander(mini, tmp);
			// ft_strstr_free(tmp);
			// tmp = NULL;
		}
		current = current->next;
		i++;
	}
}

void	ft_move_files(t_cmd *cmd, t_mini *mini)
{
	cmd->files = ft_calloc(sizeof(t_files), 1);
	cmd->files->error = 0;
	if (mini->flags->redirect && mini->flags->redirect->number != 0)
		ft_files(cmd, mini, cmd->files);
}

char	**ft_create_path(char **env)
{
	char	**path;
	int		i;

	i = -1;
	path = NULL;
	while (env[++i] != NULL)
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			path = ft_split(env[i] + 5, ':');
	}
	// if (path == NULL)
	// 	path = 
	
	return (path);
}

char	*ft_validate_comm(char *cmd, char **path)
{
	char	*command;
	char	*test;
	int		j;

	j = 0;
	if (access(cmd, X_OK) == 0 && ft_strrchr(cmd, '/'))
	{
		command = ft_strdup(cmd);
		return (command);
	}
	if (access(cmd, X_OK) != 0 && ft_strrchr(cmd, '/'))
		return (NULL); // Error 127
	command = ft_strjoin("/", cmd);
	if (path == NULL)
		return (NULL);
	while (path[j] != NULL)
	{
		test = ft_strjoin(path[j++], command);
		if (access(test, X_OK) == 0)
		{
			free(command);
			return (test);
		}
		free(test);
	}
	free(command);
	// Error 127
	return (NULL);
}

char	**ft_strstr_dup(char **str)
{
	char	**dup;
	int		i;

	i = 0;
	if (str == NULL)
		return (NULL);
	dup = (char **)ft_calloc(sizeof(char *), ft_strstr_len(str) + 1);
	if (dup == NULL)
		return (NULL);
	while (i < ft_strstr_len(str))
	{
		dup[i] = ft_strdup(str[i]);
		if (dup[i] == NULL)
		{
			ft_strstr_free(dup);
			return (NULL);
		}
		i++;
	}
	return (dup);
}

void	process_lines(t_cmd **cmd, t_mini *mini, char **lines, int i)
{
	t_cmd	*cmd_cmd;
	t_cmd	*current;

	while (lines && lines[i] != NULL)
	{
		cmd_cmd = ft_add_command(lines[i++], -1);
		
		if (*cmd == NULL)
			*cmd = cmd_cmd;
		else
		{
			current = *cmd;
			while (current->next != NULL)
				current = current->next;
			current->next = cmd_cmd;
		}
		ft_move_files(cmd_cmd, mini);
		if (mini->cmd->files->error == -1)
			return ;
	}
}

char	*ft_route_cmd(t_mini *mini, t_cmd *current, char *tmp)
{
	char	**path;
	char	*cmd;

	path = ft_create_path(mini->env->env);
	if (tmp[0] == '\0')
	{
		ft_strstr_free(path);
		current->error = -2;
		return (NULL);
	}
	if (path == NULL)
		path = ft_save_path(mini->env->env);
	cmd = ft_validate_comm(tmp, path);
	if (cmd == NULL)
	{
		printf("Ese comando no existe, prueba otro\n");
		ft_strstr_free(path);
		return (NULL); // Error 127 Crear outfiles antes de salir e imprimir
					   // "printf("mini: command not found");
					   // si infiles y outfiles no dan error.
	}
	ft_strstr_free(path);
	return (cmd);
}

int	ft_sizes(t_cmd *current)
{
	char	**tmp;
	int		size;
	int		i;

	i = -1;
	size = 0;
	tmp = ft_strstr_dup(current->args);
	while (tmp[++i])
	{
		if (ft_type(tmp[i]) != 0)
			i++;
		else
			size++;
	}
	ft_strstr_free(tmp);
	return (size);
}

void	ft_select_cmd(t_cmd *current, t_mini *mini, int j)
{
	char	**tmp;
	char	**tmp2;
	int		i;
	int		size = 0;

	i = -1;
	tmp = ft_strstr_dup(current->args);
	while (tmp[++i])
	{
		if (ft_type(tmp[i]) != 0)
			size++;
	}
	i = -1;
	if (size > 0)
		tmp2 = ft_calloc(sizeof(char *), size + 1);
	else
		tmp2 = ft_calloc(sizeof(char *), ft_strstr_len(current->args) + 1);
	while (tmp[++i])
	{
		current->error = 0;
		if (ft_type(tmp[i]) != 0)
			i++;
		else
		{
			if (j == 0)
			{
				current->cmd = ft_route_cmd(mini, current, tmp[i]);
				if (current->cmd == NULL && current->error != -2)
					mini->cmd->files->error = -1;
			}
			if (current->error != -2)
				tmp2[j++] = ft_strdup(tmp[i]);
		}
	}
	ft_strstr_free(current->args);
	current->args = NULL;
	current->args = ft_strstr_dup(tmp2);
	ft_strstr_free(tmp2);
	ft_strstr_free(tmp);
}

void	ft_remove_files(t_cmd *cmd, t_mini *mini)
{
	t_cmd	*current;

	current = cmd;
	while (current != NULL)
	{
		ft_select_cmd(current, mini, 0);
		current = current->next;
	}
}

void	ft_process_file(char *str, int *count, int *check, char **dest)
{
	if (*count > 1)
		(*count)--;
	else if (*count == 1 && *check == 0)
		*dest = ft_strdup(str);
	else if (*count == 1)
		(*count)--;
}

void	ft_select_files(t_cmd *cmd, int i)
{
	t_cmd	*current;
	t_type	*type;

	current = cmd;
	type = current->type;
	while (current != NULL)
	{
		i = -1;
		while (current->files->f_order && current->files->f_order[++i] != NULL)
		{
			if (ft_strnstr("1", current->files->order[i], 1) != NULL)
				ft_process_file(current->files->f_order[i],
					&type->infile, &type->here_doc, &type->in);
			if (ft_strnstr("2", current->files->order[i], 1) != NULL)
				ft_process_file(current->files->f_order[i],
					&type->outfile, &type->append, &type->out);
			if (ft_strnstr("3", current->files->order[i], 1) != NULL)
				ft_process_file(current->files->f_order[i],
					&type->here_doc, &type->infile, &type->in);
			if (ft_strnstr("4", current->files->order[i], 1) != NULL)
				ft_process_file(current->files->f_order[i],
					&type->append, &type->outfile, &type->out);
		}
		current = current->next;
	}
}

int	ft_minus_one(t_mini *mini)
{
	if (mini->flags->pipe == -1 || mini->flags->quote == -1
		|| mini->flags->locate_red == -1)
		return (-1);
	return (0);
}

int	ft_do_expand(t_mini *mini, t_cmd **cmd, char **lines, char *input)
{
	if (mini->flags->pipe == 0)
	{
		*(cmd) = ft_add_command(input, -1);
		ft_move_files(*(cmd), mini);
	}
	else
		process_lines(cmd, mini, lines, 0);
	ft_do_expander(mini, *cmd);
	ft_strstr_free(lines);
	if (mini->cmd->files->error == -1)
		return (-1);
	ft_remove_files(*cmd, mini);
	if (mini->cmd->files->error == -1)
		return (-1);
	ft_select_files(*cmd, 0);
	return (0);
}

int	ft_wait_bonus(t_cmd *cmd)
{
	int	state;
	int i;

	i = 0;
	while (cmd->names->proc[i] && i + 1 < cmd->names->index)
		waitpid(cmd->names->proc[i++], NULL, 0);
	waitpid(cmd->names->proc[i], &state, 0);
	return (state);
}

void	ft_start_val(t_cmd *cmd, t_mini *mini)
{
	cmd->names->fd = 0;
	cmd->names->index = 0;
	cmd->names->fd_infile = 0;
	cmd->names->fd_outfile = 1;
	cmd->names->proc = ft_calloc(sizeof(int), mini->num_comm + 1);
}

int	ft_do_comm(t_cmd *cmd, t_mini *mini)
{

	if (cmd == NULL)
	{
        printf(B_RD_0 "No command structure.\n" RESET);
        return (0);
    }
    t_cmd *current = cmd;

	mini->fd_tmp = 0;
	mini->num_comm = mini->flags->pipe + 1;
	while (current != NULL)
	{
		ft_start_val(current, mini);
		ft_comm(current, mini);
		mini->num_comm--;
		current = current->next;
	}
	ft_wait_bonus(cmd);
	return (1);
}

int	ft_strtok(t_mini *mini, t_cmd **cmd, char *input)
{
	char	**lines;
	// int		comm;

	// comm = 0;
	lines = ft_check_input(mini, input);
	if (ft_minus_one(mini) == -1)
		return (0);
	if (ft_do_expand(mini, cmd, lines, input) == -1)
		return (0);
	print_cmd(*cmd);
	// comm = ft_do_comm(*cmd, mini);
	// if (comm != 1)
	// 	return (0);
	return (1);
}