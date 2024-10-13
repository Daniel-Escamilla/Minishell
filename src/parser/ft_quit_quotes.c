/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quit_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:00:03 by descamil          #+#    #+#             */
/*   Updated: 2024/10/13 19:22:03 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static int	*ft_intdup_mod(int *dup)
{
	int	*result;

	result = ft_calloc(sizeof(int), 2);
	if (result == NULL)
		return (0);
	result[0] = dup[0];
	result[1] = dup[1];
	return (result);
}

int	ft_has_quotes(char *str, int i)
{
	i--;
	while (str && str[++i] != '\0')
		if (str[i] == '\"' || str[i] == '\'')
			return (1);
	return (0);
}

int	*ft_find_quotes(char *str, int i)
{
	int	*quotes;

	quotes = ft_calloc(sizeof(int), 2);
	while (str[i] != '\0' && str[i] != '\"' && str[i] != '\'')
		i++;
	quotes[0] = i;
	if (str[i] && str[i + 1])
	{
		quotes[1] = ft_locate_next_quote(i + 1, str, str[i]);
		if (str[quotes[1]] == '\0')
			quotes[1] = -1;
	}
	else
		quotes[1] = -1;
	return (quotes);
}

static void	ft_remove_quotes(char **str, int *pos)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (pos[0] == -1 || pos[1] == -1)
		return ;
	result = ft_calloc(sizeof(char), ft_strlen(*str) - 2 + 1);
	while (i < pos[0])
		result[j++] = (*str)[i++];
	i++;
	while (i < pos[1])
		result[j++] = (*str)[i++];
	i++;
	while ((*str)[i] != '\0')
		result[j++] = (*str)[i++];
	result[j] = '\0';
	free(*str);
	*str = result;
}

void	ft_rm_quotes(char **str, int *quotes)
{
	char	*result;
	int		*quotes2;

	if (ft_has_quotes(*str, 0) == 0)
		return ;
	result = ft_strdup(*str);
	free(*str);
	ft_remove_quotes(&result, quotes);
	while (ft_has_quotes(result, quotes[1] - 1) == 1)
	{
		quotes2 = ft_find_quotes(result, quotes[1] - 1);
		ft_remove_quotes(&result, quotes2);
		free(quotes);
		quotes = ft_intdup_mod(quotes2);
		free(quotes2);
	}
	free(quotes);
	*str = result;
}
