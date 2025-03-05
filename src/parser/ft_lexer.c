/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:50:54 by smarin-a          #+#    #+#             */
/*   Updated: 2025/03/05 10:16:02 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static void	ft_free_per_comm(t_mini *mini, char *input)
{
	if (mini->input)
	{
		free(mini->input);
		mini->input = NULL;
	}
	if (mini->flags->redirect && input != NULL)
	{
		mini->flags->locate_red = 0;
		free(mini->flags->redirect);
		mini->flags->redirect = NULL;
	}
	if (mini->proc && mini->error != -2 && ft_nothing(input, 0) != 1)
		free(mini->proc);
	if (input)
		free(input);
	if (mini->files)
	{
		ft_strstr_free(mini->files);
		mini->files = NULL;
	}
	mini->here_doc_index = 0;
	mini->single = 0;
}

static int	ft_handle_input(t_mini *mini, char *input)
{
	if (!input)
	{
		if (mini->flags->pipe != 0)
			return (0);
		printf("exit\n");
		return (0);
	}
	if (ft_nothing(input, 0) == 1)
		return (1);
	return (2);
}

void	ft_unlink_hd(t_mini *mini)
{
	int	dup_fd;
	int	fd;
	int	i;

	i = 0;
	fd = 2;
	while (++fd < 1024)
	{
		dup_fd = -1;
		if (fd != mini->fd_history)
			dup_fd = dup(fd);
		if (dup_fd != -1)
		{
			close(fd);
			close(dup_fd);
		}
	}
	if (mini->files)
	{
		while (mini->files[i])
			unlink(mini->files[i++]);
	}
}

static char	*ft_tty(void)
{
	char	*input;
	char	*input2;

	input2 = get_next_line(STDIN_FILENO);
	input = ft_strtrim(input2, "\n");
	if (input2)
		free(input2);
	return (input);
}

void	ft_recive_input(t_mini *mini)
{
	char	*input;

	mini->fd_history = ft_history();
	while (1)
	{
		if (mini->tty == 0)
			input = readline("🐚"B_GR_0" MINI(S)HELL"RESET" 🔥 -> ");
		else if (mini->tty >= 1 && mini->tty++ >= 1)
			input = ft_tty();
		if (ft_handle_input(mini, input) == 0)
			break ;
		else if (ft_handle_input(mini, input) == 2)
		{
			mini->input = ft_strdup(input);
			add_history(input);
			if (mini->fd_history != -1)
				if (write(mini->fd_history, input, ft_strlen(input)) == -1
					|| write(mini->fd_history, "\n", 1) == -1)
					return ;
			ft_strtok(mini, &(mini->cmd), input);
			ft_unlink_hd(mini);
		}
		ft_free_per_comm(mini, input);
		free_t_cmd(&(mini->cmd));
	}
}
