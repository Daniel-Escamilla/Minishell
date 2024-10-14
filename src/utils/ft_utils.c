/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:24:41 by smarin-a          #+#    #+#             */
/*   Updated: 2024/10/13 19:59:03 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

void	ft_mini_header(void)
{
	printf("\n");
	printf("               ");
	printf(B_RD_0"╭──────╮╭╮ ╭╮ ╭─╮╭╮ ╭╮ ╭╮ ╭─╮ ╭─╮ ╭───╮ ╭─╮   ╭─╮  \n"RESET);
	printf("               ");
	printf(B_OR_1"│ ╭╮╭╮ │ │ │  │ ╰╯│  │ │  │ ╰─╯ │ │ ─╮╯ │ │   │ │  \n"RESET);
	printf("               ");
	printf(B_OR_0"│ │╰╯│ │ │ │  │╭╮ │  │ │  │ ╭─╮ │ │ ─╯╮ │ ╰─╮ │ ╰─╮\n"RESET);
	printf("               ");
	printf(B_YE_0"╰─╯  ╰─╯╰╯ ╰╯ ╰╯╰─╯ ╰╯ ╰╯ ╰─╯ ╰─╯ ╰───╯ ╰───╯ ╰───╯\n"RESET);
	printf("\n\n                ");
	printf(B_WH_2"         ╭─────────────────────────────╮            "RESET);
	printf(B_WH_2"\n                         │"RESET);
	printf(B_WH_0"   By Descamil && Smarin-a   "RESET);
	printf(B_WH_2"│            \n                "RESET);
	printf(B_WH_2"         ╰─────────────────────────────╯            "RESET);
	printf("\n\n\n");
}

int	ft_history(void)
{
	char	*str;
	char	*tmp;
	int		fd;

	if (access(".minishell_history", W_OK) == -1)
		unlink(".minishell_history");
	fd = open(".minishell_history", O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		ft_printf_exit("mini: error create file: ", ".minihsell_history", 1);
	while (1)
	{
		tmp = get_next_line(fd);
		if (tmp == NULL)
			break ;
		str = ft_strtrim(tmp, "\n");
		add_history(str);
		free(tmp);
		free(str);
	}
	if (tmp)
		free(tmp);
	return (fd);
}

void	ft_strstr_printf(char **str)
{
	int	i;

	i = -1;
	if (str)
	{
		while (str[++i])
			printf("%s\n", str[i]);
	}
}

void	safe_close(int *fd)
{
	if (*fd > 2)
		close(*fd);
}
