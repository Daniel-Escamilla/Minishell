/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:50:54 by smarin-a          #+#    #+#             */
/*   Updated: 2024/08/18 18:02:27 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_history(void)
{
	char	*str;
	char	*tmp;
	int		fd;

	if (access(".minishell_history", W_OK) == -1)
		unlink(".minishell_history");
	fd = open(".minishell_history", O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		ft_error("Error create file", 1);
	while (1)
	{
		tmp = get_next_line(fd);
		if (tmp == NULL)
			break ;
		str = ft_strtrim(tmp, "\n");
		add_history(str);
		free(tmp);
		free(str);
	}
	if (tmp)
		free(tmp);
	return (fd);
}

static int	ft_check_void_input(char *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i] != '\0')
		j += ft_isspace(input[i++]);
	if (j == i)
		return (-1);
	return (0);
}

char	*ft_free_input(t_mini *mini, char *input)
{
	int	j;

	j = 0;
	while (input && input[j] == ' ')
		j++;
	if (input[j] != '\0')
	{
		if (mini->cmd)
		{
			if (mini->cmd->args)
			{
				j = 0;
				while (mini->cmd->args[j] && mini->cmd->args[j] != NULL)
					ft_strstr_free(mini->cmd->args);
			}
		}
	}
	free(input);
	return (NULL);
}

int	ft_find_exit(char *input)
{
	char	*exit_position;

	exit_position = ft_strnstr(input, "exit", ft_strlen(input));
	if (exit_position != NULL)
	{
		exit_position += 4;
		while (*exit_position == ' ')
			exit_position++;
		if (*exit_position == '\0')
			return (1);
	}
	return (0);
}

void	ft_recive_input(t_mini *mini)
{
	char	*input;
	
	mini->fd_history = ft_history();
	while (1)
	{
		input = readline("🐚"B_GR_0" MINI(S)HELL"RESET" 🔥 -> ");
		if (!input)
			ft_exit_error(mini, "Exit", g_exit_status);
		if (ft_check_void_input(input) == -1 || input[0] == '\0')
			(void)input;
		else
		{
			mini->input = ft_strdup(input);
			add_history(input);
			if (mini->fd_history != -1)
			{
				write(mini->fd_history, input, ft_strlen(input));
				write(mini->fd_history, "\n", 1);
			}
			// TODO: HECHO HASTA AQUI y funcional COn señales incluidas
			// ? HASTA AQUI FUNCIONA TODO (CREO)
			// ! Nucleo del parseo
			// El parseo no funciona
			// este proyecto es una mierda
			// No se que mas hacer
			// ! AYUDA:
			if (ft_strtok(mini, &(mini->cmd), input) && mini->flags->quote != 0)
			{
				printf("\n\nLlega al final! 🚀\n\n");
			}
			free(mini->input);
		}
		if (mini->flags->redirect && input != NULL)
		{
			mini->flags->locate_red = 0;
			free(mini->flags->redirect);
			mini->flags->redirect = NULL;  //Utilzar funcion nueva
		}
		if (input)
			free(input);
		// print_cmd(mini->cmd);

		free_t_cmd(&(mini->cmd));
	}
	close(mini->fd_history);
}
