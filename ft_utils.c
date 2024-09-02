/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:24:41 by smarin-a          #+#    #+#             */
/*   Updated: 2024/09/02 14:52:41 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	printf("\n                ");
	printf(B_RD_0"         ╭─────────────────────────────╮            "RESET);
	printf("\n                ");
	printf(B_OR_1"         │   By Descamil && Smarin-a   │            "RESET);
	printf("\n                ");
	printf(B_YE_0"         ╰─────────────────────────────╯            "RESET);
	printf("\n\n\n");
}

int	ft_strnstrstr(char **str, char *locate)
{
	int	i;
	int	total;

	i = 0;
	total = 0;
	if (str)
	{
		while (str[i])
		{
			if (ft_strncmp(str[i], locate, ft_strlen(locate)) == 0)
				total++;
			i++;
		}
	}
	return (total);
}

int	ft_strstr_len(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != NULL)
		i++;
	return (i);
}

char	**ft_strstr_join(char **str, char **str1)
{
	char	**string;
	int		size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (str == NULL)
	{
		string = ft_calloc(sizeof(char *), ft_strstr_len(str1) + 1);
		while (i != ft_strstr_len(str1) && str[i] != NULL)
			string[j++] = ft_strdup(str1[i++]);
		return (string);
	}
	size = ft_strstr_len(str) + ft_strstr_len(str1);
	string = ft_calloc(sizeof(char *), size + 1);
	if (string == NULL)
		return (NULL);
	while (i != ft_strstr_len(str) && str[i] != NULL)
		string[j++] = ft_strdup(str[i++]);
	i = 0;
	while (i != ft_strstr_len(str1) && str1[i] != NULL)
		string[j++] = ft_strdup(str1[i++]);
	string[j] = NULL;
	return (string);
}

void	ft_strstr_free(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
			free(str[i++]);
		free(str);
	}
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
