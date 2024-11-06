/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:53:31 by descamil          #+#    #+#             */
/*   Updated: 2024/11/06 19:18:21 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

// static int	ft_is_a_flag(char *flag)
// {
// 	int	i;

// 	i = 1;
// 	if (flag && flag[0] && flag[0] != '-')
// 		return (2);
// 	while (flag[i] && flag[i] == 'n')
// 		i++;
// 	if (flag[i] == '\0')
// 		return (1);
// 	return (2);
// }

// static void	ft_write_args(char **args)
// {
// 	int	flag;
// 	int	i;

// 	i = 1;
// 	flag = 0;
// 	while (args[i])
// 	{
// 		if (flag != 2)
// 			flag = ft_is_a_flag(args[i]);
// 		if (flag != 1)
// 			printf("%s", args[i]);
// 		i++;
// 		if (args[i] != NULL && flag != 1)
// 			printf(" ");
// 	}
// }

// int	ft_echo(t_cmd *cmd)
// {
// 	int	flag;
// 	int	i;

// 	if (ft_strstr_len(cmd->args) == 1)
// 		return (0);
// 	i = 1;
// 	flag = 0;
// 	flag = ft_is_a_flag(cmd->args[i]);
// 	while (cmd->args[i] && flag != 1)
// 		flag = ft_is_a_flag(cmd->args[i++]);
// 	ft_write_args(cmd->args);
// 	if (flag != 1)
// 		printf("\n");
// 	return (0);
// }

static int	ft_is_a_flag(char *flag)
{
	int	i;

	i = 1;
	if (flag && flag[0] == '-' && flag[1] == 'n' && flag[2] == '\0')
		return (1);
	return (2);
}

static void	ft_write_args(char **args, int flag)
{
	int	i;

	i = 1;
	while (args[i])
	{
		printf("%s", args[i]);
		i++;
		if (args[i] != NULL)
			printf(" ");
	}
}

int	ft_echo(t_cmd *cmd)
{
	int	flag;
	int	i;

	if (ft_strstr_len(cmd->args) == 1)
		return (0);

	i = 1;
	flag = 0;

	if (cmd->args[i] && ft_is_a_flag(cmd->args[i]) == 1)
	{
		flag = 1;
		i++;
	}

	ft_write_args(cmd->args, flag);

	if (flag != 1)
		printf("\n");

	return (0);
}
