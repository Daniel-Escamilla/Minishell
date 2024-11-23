/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:53:53 by descamil          #+#    #+#             */
/*   Updated: 2024/11/23 11:51:40 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int	ft_pwd(t_cmd *cmd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (1);
	write(cmd->names->fd_outfile, pwd, ft_strlen(pwd));
	write(cmd->names->fd_outfile, "\n", 1);
	free(pwd);
	return (0);
}
