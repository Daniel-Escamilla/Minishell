/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_div.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:16:59 by user              #+#    #+#             */
/*   Updated: 2024/09/12 19:53:01 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_no_dollar(int *iter, char *div, char *str)
{
	char	*result;

	*iter = -2;
	result = ft_no_more_dolar(div, str);
	return (result);
}

char	*handle_existing_div(int *iter, char *str, char *div)
{
	char	*result;

	result = NULL;
	if (ft_strchr_mod(div, '$', 0) == NULL)
	{
		*iter = -2;
		result = div;
	}
	else
	{
		if (str != NULL && *iter != 1)
			str = ft_free_null(str);
		str = ft_calloc(sizeof(char), ft_strlen(div) + 1);
		ft_strlcpy(str, div, ft_strlen(div) + 1);
		free(div);
	}
	return (result);
}

char	*process_dollar(char *str, char **env, int *stop)
{
	char	**div_tmp;
	char	*tmp;
	char	*div;
	char	*res;

	res = ft_strchr_mod(str, '$', *stop);
	div_tmp = ft_tript(str, ft_size_var(res), res - str);
	div_tmp[1] = ft_dolar_to_iqual(div_tmp[1]);
	tmp = ft_change_var(div_tmp[1], env);
	if (ft_strlen(tmp) == 1 && ft_strncmp(tmp, "$", 1) == 0)
		(*stop)++;
	div = ft_join(div_tmp, tmp);
	ft_ex_free(div_tmp, tmp);
	return (div);
}

char	*expand_div(int *iter, char *str, char **env)
{
	char	*result;
	char	*div;
	int		stop;

	stop = 0;
	div = NULL;
	if ((ft_strchr_mod(str, '$', stop) - str) < 0)
		result = handle_no_dollar(iter, div, str);
	else
	{
		if (*iter == -1)
			*iter = 0;
		if (div != NULL)
		{
			result = handle_existing_div(iter, str, div);
			if (result != NULL)
				return (result);
		}
		result = process_dollar(str, env, &stop);
	}
	return (result);
}

// char	*expand_div(int *iter, char **str, char **env)
// {
// 	char	**div_tmp;
// 	char	*div;
// 	char	*tmp;
// 	char	*res;
// 	int		stop;

// 	div_tmp = NULL;
// 	div = NULL;
// 	tmp = NULL;
// 	stop = 0;
// 	if ((ft_strchr_mod(*str, '$', stop) - *str) < 0)
// 	{
// 		*iter = -2;
// 		return (ft_no_more_dolar(div, *str));
// 	}
// 	if (*iter == -1)
// 		*iter = 0;
// 	if (div && ft_strchr_mod(div, '$', stop) == NULL)
// 	{
// 		*iter = -2;
// 		return (div);
// 	}
// 	if (div != NULL)
// 	{
// 		if (*str != NULL && *iter != 1)
// 			*str = ft_free_null(*str);
// 		*str = ft_calloc(sizeof(char), ft_strlen(div) + 1);
// 		ft_strlcpy(*str, div, ft_strlen(div) + 1);
// 		free(div);
// 	}
// 	res = ft_strchr_mod(*str, '$', stop);
// 	div_tmp = ft_tript(*str, ft_size_var(res), res - *str);
// 	div_tmp[1] = ft_dolar_to_iqual(div_tmp[1]);
// 	tmp = ft_change_var(div_tmp[1], env);
// 	if (ft_strlen(tmp) == 1 && ft_strncmp(tmp, "$", 1) == 0)
// 		stop += 1;
// 	div = ft_join(div_tmp, tmp);
// 	ft_ex_free(div_tmp, tmp);
// 	return (div);
// }
