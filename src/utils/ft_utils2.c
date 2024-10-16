/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:42:03 by descamil          #+#    #+#             */
/*   Updated: 2024/10/13 20:01:18 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

void	ft_perror_exit(char *error, int exit)
{
	perror(error);
	g_exit_status = exit;
}

void	ft_printf_exit(char *error, char *arguments, int exit)
{
	printf("%s%s", error, arguments);
	g_exit_status = exit;
}
