/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 09:30:16 by descamil          #+#    #+#             */
/*   Updated: 2024/09/03 09:30:56 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_sindub_join(char **str, char *str1)
{
	char	**result;
	int		len;
	int		i;

	i = -1;
	if (str == NULL)
		len = 0;
	else
		len = ft_strstr_len(str);
	result = ft_calloc(sizeof(char *), len + 1 + 1);
	while (++i < len)
		result[i] = ft_strdup(str[i]);
	result[i] = ft_strdup(str1);
	return (result);
}

void	ft_strstr_unlink(t_mini *mini)
{
	int	i;

	i = -1;
	while (mini->join && mini->join[++i])
		unlink(mini->join[i]);
}
