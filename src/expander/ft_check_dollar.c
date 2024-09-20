/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:10:53 by smarin-a          #+#    #+#             */
/*   Updated: 2024/09/20 21:07:38 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "expander.h"

// static char	*ft_remove_dollar_n_digits(char *command, int i, int j)
// {
// 	char	*temp;

// 	while (command[++i])
// 	{
// 		if (command[i] && command[i] == '$' && command[i + 1]
// 			&& ft_isdigit_n_special_char(command[i + 1]) == 1)
// 		{
// 			j = -1;
// 			temp = ft_calloc(sizeof(char), ft_strlen(command) - 1);
// 			if (!temp)
// 				ft_exit_error(NULL, "Malloc error", 15);
// 			while (++j < i)
// 				temp[j] = command[j];
// 			i++;
// 			while (command[++i])
// 				temp[j++] = command[i];
// 			free(command);
// 			command = ft_remove_dollar_n_digits(temp, -1, -1);
// 		}
// 	}
// 	return (command);
// }

// int	ft_isdigit_n_special_char(int i)
// {
// 	if (i == '*' || i == '@' || i == 92 || (i >= 48 && i <= 57))
// 		return (1);
// 	return (0);
// }

// int	ft_check_dollar_n_digits(char *command, int i)
// {
// 	while (command[++i] && command[i] != '$')
// 		;
// 	if (command[i] && command[i] == '$' && command[i + 1]
// 		&& ft_isdigit_n_special_char(command[i + 1] == 1))
// 		return (0);
// 	return (1);
// }
