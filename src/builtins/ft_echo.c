/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:53:31 by descamil          #+#    #+#             */
/*   Updated: 2025/02/22 11:33:47 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static int	ft_is_a_flag(char *flag)
{
	int	i;

	i = 1;
	if (flag && flag[0] && flag[0] != '-')
		return (2);
	while (flag[i] && flag[i] == 'n')
		i++;
	if (flag[i] == '\0')
		return (1);
	return (2);
}

static void	ft_write_args(char **args)
{
	int	flag;
	int	i;

	i = 1;
	flag = 0;
	while (args[i])
	{
		if (flag != 2)
			flag = ft_is_a_flag(args[i]);
		if (flag != 1)
			write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		i++;
		if (args[i] != NULL && flag != 1)
			write(STDOUT_FILENO, " ", 1);
	}
}

int	ft_echo(t_cmd *cmd)
{
	int	flag;

	if (ft_strstr_len(cmd->args) == 1)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	flag = ft_is_a_flag(cmd->args[1]);
	ft_write_args(cmd->args);
	if (flag != 1)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
