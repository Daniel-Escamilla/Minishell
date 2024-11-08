/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:50:54 by smarin-a          #+#    #+#             */
/*   Updated: 2024/11/09 00:10:28 by descamil         ###   ########.fr       */
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
	if (mini->proc && mini->error != -2
		&& ft_nothing(input, 0) == 0)
	{
		free(mini->proc);
		mini->proc = 0;
	}
	if (input)
		free(input);
	mini->single = 0;
}

static int	ft_handle_input(t_mini *mini, char *input)
{
	char		*term;
	char	*terms[] = {"wsvt25", "wsvt25m", "linux", "xterm-color",
		"xterm-vt220", "xterm-256color", "xterm-mono", "xterm-r5", "xterm-r6",
		"xterm", "xterm-xfree86", "hurd", "vt102", "vt52", "vt100", "vt220",
		"Eterm", "pcansi", "tmux-256color", "tmux", "mach-bold", "mach-gnu",
		"mach-gnu-color", "mach-color", "mach", "screen-256color",
		"screen.xterm-256color", "screen-w", "screen-s", "screen", "sun",
		"screen-256color-bce", "screen-bce", "ansi", "cygwin", "cons25",
		"rxvt-unicode", "rxvt-unicode-256color", "rxvt-basic", "rxvt", NULL};

	if (!input)
	{
		printf("exit");
		term = ft_get_var(mini->env->env, "TERM");
		if (ft_strnstrstr(terms, term) != 0)
			printf("\n");
		return (0);
	}
	if (ft_nothing(input, 0) == 1)
		return (1);
	return (2);
}

void	ft_recive_input(t_mini *mini)
{
	char	*input;

	mini->fd_history = ft_history();
	while (1)
	{
		input = readline("🐚"B_GR_0" MINI(S)HELL"RESET" 🔥 -> ");
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
		}
		ft_free_per_comm(mini, input);
		free_t_cmd(&(mini->cmd));
	}
	close(mini->fd_history);
	mini->fd_history = -1;
}
