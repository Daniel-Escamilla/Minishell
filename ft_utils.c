/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:24:41 by smarin-a          #+#    #+#             */
/*   Updated: 2024/08/26 13:06:01 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_mini_header(void)
{
	printf("\n\n");
	printf(B_RD_0"   *    (        )  (       )       (     (     \n"RESET);
	printf(B_OR_1"(  `   )\\ )  ( /(  )\\ ) ( /(       )\\ )  )\\ )  \n"RESET);
	printf(B_YE_2")\\))( (()/(  )\\())(()/( )\\()) (   (()/( (()/(  \n"RESET);
	printf(B_OR_2"((_)()\\ /(_))((_)\\  /(_))(_)\\  )\\   /(_)) /(_) \n"RESET);
	printf(B_OR_1"( ()(( )( ))   (( ) ( ))   (( )(( ) ( ))  ( ))   \n"RESET);
	printf(B_WH_0"|¯¯\\/¯¯||\u0305_¯\u0305_||¯\\|¯||\u0305_¯\u0305_||");
	printf(B_WH_0"¯|_|¯||¯\u0305_\u0305_||¯|   |¯|    \n"RESET);
	printf(B_WH_0"| |\\/| | | | | .` | | | |     || _| | |__ | |__  \n"RESET);
	printf(B_WH_0"|_|  |_||\u0305__\u0305_||_|\\_||\u0305__\u0305"RESET);
	printf(B_WH_0"_||_|\u0305 |_||___||____||____| \n\n"RESET);
	printf(B_RD_0"\n            By Descamil && Smarin-a\n"RESET);
	printf("\n\n");
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

// int main()
// {
// 	char	**str = ft_calloc(3, sizeof(char *));
// 	char	**str1 = ft_calloc(4, sizeof(char *));
// 	char	**string;

// 	str[0] = "Random String 1";
//     str[1] = "Random String 2";
// 	str[2] = NULL;

//     str1[0] = "Random String A";
//     str1[1] = "Random String B";
//     str1[2] = "Random String C";
// 	str1[3] = NULL;
	
// 	string = ft_strstr_join(str, str1);

// 	free(str);
// 	free(str1);
// 	int	i = -1;
// 	while (string[++i])
// 	{
// 		printf("string[%d] --> %s\n", i, string[i]);
// 	}
// 	ft_free_strstr(string);
// 	return (0);
// }