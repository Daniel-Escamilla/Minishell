/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_div.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:16:59 by user              #+#    #+#             */
/*   Updated: 2024/10/24 12:01:37 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

static char	*handle_no_dollar(int *iter, char *div, char *str)
{
	char	*result;

	*iter = -2;
	result = ft_no_more_dolar(div, str);
	return (result);
}

static char	*process_dollar(char *str, char **env, int *stop)
{
	char	**div_tmp;
	char	*tmp;
	char	*div;
	char	*res;

	res = ft_strchr_mod(str, '$', *stop);
	div_tmp = ft_tript(str, ft_size_var(res), (int)(res - str));
	div_tmp[1] = ft_dolar_to_iqual(div_tmp[1]);
	tmp = ft_change_var(div_tmp[1], env, 0);
	if ((ft_strlen(tmp) == 1 && ft_strncmp(tmp, "$", 1) == 0)
		|| (ft_strchr_mod(tmp, '$', *stop) != NULL))
		(*stop)++;
	div = ft_join(div_tmp, tmp);
	ft_ex_free(div_tmp, tmp);
	return (div);
}

char	*expand_div(int *iter, char *str, char **env, int *stop)
{
	char	*result;
	char	*div;

	div = NULL;
	result = "";
	if ((ft_strchr_mod(str, '$', *stop) - str) < 0)
		result = handle_no_dollar(iter, div, str);
	else if ((ft_strchr_mod(str, '$', *stop) - str) == 0
		&& ((*(str + 1) == ' ') || (*(str + 1) == '\0')) && --(*iter) == -2)
		return (ft_strdup("$"));
	else
	{
		if (*iter == -1)
			*iter = 0;
		result = process_dollar(str, env, *(&stop));
	}
	return (result);
}
