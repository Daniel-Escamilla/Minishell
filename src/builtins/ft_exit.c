/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:53:43 by descamil          #+#    #+#             */
/*   Updated: 2025/02/22 11:52:15 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static int	handle_sign(char *str, int *i, int *sign)
{
	if (str[*i] == '-')
	{
		*sign = -1;
		(*i)++;
	}
	else if (str[*i] == '+')
		(*i)++;
	else
		return (0);
	return (1);
}

static long long	calculate_result( char *str, int *i, int *error, int sign)
{
	long long	result;
	int			digit;

	result = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		digit = str[*i] - '0';
		if (sign == 1 && (result > (LLONG_MAX / 10)
				|| (result == (LLONG_MAX / 10) && digit > 7)))
		{
			*error = 2;
			return (LLONG_MAX);
		}
		else if (result > (LLONG_MAX / 10)
			|| (result == (LLONG_MAX / 10) && digit > 8))
		{
			*error = 2;
			return (LLONG_MIN);
		}
		result = result * 10 + digit;
		(*i)++;
	}
	return (result);
}

static long long	ft_atoll_mod(char *str, int *error)
{
	long long	result;
	int			sign;
	int			i;

	i = 0;
	sign = 1;
	*error = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (handle_sign(str, &i, &sign) && (str[i] == '-'
			|| str[i] == '+' || !(str[i] >= '0' && str[i] <= '9')))
	{
		*error = 3;
		return (0);
	}
	result = calculate_result(str, &i, error, sign);
	if (str[i] != '\0')
	{
		*error = 2;
		return (0);
	}
	return (result * sign);
}

int	ft_exit(t_mini *mini, t_cmd *cmd)
{
	long long	atoll;
	int			error;

	if (cmd->args[1])
		atoll = ft_atoll_mod(cmd->args[1], &error);
	if (mini->single)
		write(1, "exit\n", 6);
	if (cmd->args[1] && cmd->args[2] != NULL && error != 2 && error != 3)
	{
		write(2, "mini: exit: too many arguments\n", 32);
		return (1);
	}
	close(mini->fd_pipe[0]);
	close(mini->fd_pipe[1]);
	close(mini->fd_history);
	if (cmd->args[1] == NULL)
		exit(0);
	if (error == 2 || error == 3)
	{
		write(2, "mini: exit: ", 13);
		write(2, cmd->args[1], ft_strlen(cmd->args[1]));
		write(2, ": numeric argument required\n", 29);
		exit(2);
	}
	exit((int)(atoll % 256));
}
