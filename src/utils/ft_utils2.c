/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:42:03 by descamil          #+#    #+#             */
/*   Updated: 2024/11/23 16:24:22 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

void	ft_perror_exit(char *error, int exit)
{
	perror(error);
	g_exit_status = exit;
}

void	ft_printf_exit(char *error, char *arguments, int status)
{
	if (status == 126)
		ft_putstr_fd("mini: ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd(arguments, 2);
	g_exit_status = status;
	if (status == 127 || status == 126 || status == 139)
		exit(status);
}
