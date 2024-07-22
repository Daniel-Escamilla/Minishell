/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:37:59 by smarin-a          #+#    #+#             */
/*   Updated: 2024/07/11 09:41:24 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir_type(char *splited_arg)
{
	int	i;

	i = -1;
	while (splited_arg[i])
	{
		if (splited_arg[i] == 34 || splited_arg[i] == 39)
			i = ft_locate_next_quote(i + 1, splited_arg, splited_arg[i]) + 1;
		if (splited_arg[i] == '>' && !ft_is_not_mayor_n_minor_char(splited_arg[i + 1]))
			return (1);
		if (splited_arg[i] == '>' && splited_arg[i + 1] == '>' && !ft_is_not_mayor_n_minor_char(splited_arg[i + 2]))
			return (2);
		if (splited_arg[i] == '<' && !ft_is_not_mayor_n_minor_char(splited_arg[i + 1]))
			return (3);
		if (splited_arg[i] == '<' && splited_arg[i + 1] == '<' && !ft_is_not_mayor_n_minor_char(splited_arg[i + 2]))
			return (4);
		if (splited_arg[i] == '2' && splited_arg[i + 1] == '>' && !ft_is_not_mayor_n_minor_char(splited_arg[i + 2]))
			return (5);
		if (splited_arg[i] == '2' && splited_arg[i + 1] == '>' && splited_arg[i + 2] == '>' && !ft_is_not_mayor_n_minor_char(splited_arg[i + 3]))
			return (6);
		if (ft_is_not_mayor_n_minor_char(splited_arg[i]))
			return (-1);
	}
	return (0);
}

int	ft_check_redir_arg(char **splited_pipes_matrix, int i)
{
	int		j;
	char	*temp;

	j = 0;
	if (ft_redir_type(splited_pipes_matrix[i]) == -1)
	{
		ft_put_error("bash", NULL, "syntax error near unexpected token `>'");
		return (-1);
	}
	temp = ft_strchr(splited_pipes_matrix[i], ft_type_of_operator_char(ft_redir_type(splited_pipes_matrix[i])));
	while (temp && ft_redir_type(temp + j))
	{
		j = 0;
		while (temp[j] && (temp[j] == 32 || ft_is_not_mayor_n_minor_char(temp[j])))
			j++;
		if ((ft_redir_type(splited_pipes_matrix[i]) && !temp[j]) || ft_is_not_mayor_n_minor_char(temp[ft_strlen(temp) - 1]))
		{
			ft_put_error("bash", NULL, "syntax error near unexpected token `>'");
			return (-1);
		}
		temp = ft_strchr(temp + j, ft_type_of_operator_char(ft_redir_type(temp + j)));
	}
	return (0);
}
