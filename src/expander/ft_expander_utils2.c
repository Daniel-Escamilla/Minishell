/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:15:16 by user              #+#    #+#             */
/*   Updated: 2024/09/21 12:27:27 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

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

char	*ft_no_more_dolar(char *div, char *str)
{
	if (!div)
		div = ft_strdup(str);
	return (div);
}

char	*ft_free_null(char *str)
{
	free(str);
	return (NULL);
}
