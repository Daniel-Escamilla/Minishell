/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:20:46 by descamil          #+#    #+#             */
/*   Updated: 2024/09/02 15:37:08 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr_mod(char *str, int value, int stop)
{
	char	quote;
	int		i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == '\"')
		{
			quote += 1;
			if (quote == 2)
				quote = 0;
		}
		else if (str[i] == '\'' && quote == 0)
		{
			i = ft_locate_next_quote(i + 1, str, str[i]);
			if (str[i] == '\0')
				return (NULL);
		}
		if (str && str[i] == value && stop-- == 0)
			return (str + i);
	}
	return (NULL);
}

char	**ft_tript(char *str, int size, int start)
{
	char	**div;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (size == -1)
		size = 1;
	div = (char **)ft_calloc(sizeof(char *), 4);
	if (div == NULL)
		return (NULL);
	if (start != 0)
	{
		div[0] = ft_calloc(sizeof(char), start + 1);
		if (div[0] == NULL)
			return (NULL);
		while (++i < start)
			div[0][i] = str[i];
	}
	else
		div[++i] = NULL;
	div[1] = ft_calloc(sizeof(char), size + 1);
	if (div[1] == NULL)
		return (NULL);
	while (j < size)
		div[1][j++] = str[i++];
	if ((int)ft_strlen(str) > size + start)
	{
		div[2] = ft_calloc(sizeof(char), (ft_strlen(str) - start + size + 1));
		if (div[2] == NULL)
			return (NULL);
		j = 0;
		while (str[i] != '\0')
			div[2][j++] = str[i++];
	}
	else
		div[2] = NULL;
	return (div);
}

char	*ft_change_var(char *div, char **env)
{
	char	*glob;
	char	*str;
	int		i;

	i = -1;
	if (div && ft_strlen(div) == 1 && ft_strncmp(div, "$", 1) == 0)
	{
		str = ft_calloc(sizeof(char), 2);
		if (str == NULL)
			return (NULL);
		ft_memset(str, '$', 1);
		return (str);
	}
	if (div && ft_strlen(div) == 2 && ft_strncmp(div, "?=", 2) == 0)
	{
		str = ft_calloc(sizeof(char), ft_strlen(glob) + 1);
		if (str == NULL)
			return (NULL);
		ft_memcpy(str, glob, ft_strlen(glob) + 1);
		free(glob);
		return (str);
	}
	while (env[++i] != NULL)
	{
		if (ft_strnstr(env[i], div, ft_strlen(div)) != NULL)
		{
			if (str)
				free(str);
			str = ft_calloc(sizeof(char), ft_strlen(env[i]) - ft_strlen(div) + 1);
			if (str == NULL)
				return (NULL);
			ft_memcpy(str, env[i] + ft_strlen(div), ft_strlen(env[i]) - ft_strlen(div) + 1);
			if (str != NULL)
				return (str);
		}
	}
	return ("");
}

char	*ft_dolar_to_iqual(char *div)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if (ft_strncmp(div, "$", 1) == 0 && ft_strlen(div) == 1)
		return (div);
	while (div[j] != '\0')
		div[i++] = div[j++];
	if (div[j] == '\0')
		div[i] = '=';
	return (div);
}

char	*ft_join(char **div, char *tmp)
{
	char	*ptr;
	char	*final;

	ptr = NULL;
	final = NULL;
	if (div[0] == NULL && div[2] == NULL)
	{
		final = ft_calloc(sizeof(char), ft_strlen(tmp) + 1);
		ft_strlcpy(final, tmp, ft_strlen(tmp) + 1);
	}
	else if (div[0] != NULL && div[2] == NULL)
		final = ft_strjoin(div[0], tmp);
	else if (div[2] != NULL && div[0] == NULL)
		final = ft_strjoin(tmp, div[2]);
	else
	{
		if (div != NULL)
			ptr = ft_strjoin(div[0], tmp);
		if (ptr != NULL)
		{
			final = ft_strjoin(ptr, div[2]);
			free(ptr);
		}
	}
	if (final)
		return (final);
	return (tmp);
}

int	ft_size_var(char *str)
{
	int	i;

	i = 1;
	if (str[i] == '$' || str[i] == '?')
		return (++i);
	if (str[i] == ' ' || str[i] == '\0')
		return (-1);
	while (ft_isalnum(str[i]) == 1)
		i++;
	return (i);
}

void	ft_ex_free(char **div, char *tmp)
{
	if (div)
	{
		free(div[0]);
		if (div[1])
			free(div[1]);
		free(div[2]);
		free(div);
	}
	if (tmp && ft_strlen(tmp) != 0)
		free(tmp);
}

char	*ft_expander(char **env, char *str)
{
	char	**div;
	char	*tmp;
	char	*div_tmp;
	char	*cpy;
	int		iter;
	int		stop;
	char	*res;
	int		value;

	stop = 0;
	iter = -1;
	div = NULL;
	tmp = NULL;
	div_tmp = NULL;
	if (str == NULL)
		return (NULL);
	cpy = ft_strdup(str);
	while (1)
	{
		value = ft_strchr_mod(str, '$', stop) - str;
		if (value < 0)
		{
			free(cpy);
			if (!div_tmp)
				div_tmp = ft_strdup(str);
			return (div_tmp);
		}
		if (iter == -1)
			iter = 0;
		if (div_tmp && ft_strchr_mod(div_tmp, '$', stop) == NULL)
			break ;
		if (div_tmp != NULL)
		{
			if (str != NULL && iter != 1)
			{
				free(str);
				str = NULL;
			}
			str = ft_calloc(sizeof(char), ft_strlen(div_tmp) + 1);
			ft_strlcpy(str, div_tmp, ft_strlen(div_tmp) + 1);
			free(div_tmp);
		}
		res = ft_strchr_mod(str, '$', stop);
		div = ft_tript(str, ft_size_var(res), res - str);
		div[1] = ft_dolar_to_iqual(div[1]);
		tmp = ft_change_var(div[1], env);
		if (ft_strlen(tmp) == 1 && ft_strncmp(tmp, "$", 1) == 0)
			stop += 1;
		div_tmp = ft_join(div, tmp);
		ft_ex_free(div, tmp);
		iter++;
	}
	if (str && iter != 1 && (int)ft_strlen(str) != 0
		&& ft_strncmp(str, cpy, ft_strlen(cpy)) != 0)
		free(str);
	free(cpy);
	return (div_tmp);
}
