/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:20:46 by descamil          #+#    #+#             */
/*   Updated: 2024/09/12 19:54:39 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expander(char **env, char *str)
{
	char	*cpy;
	char	*div;
	char	*tmp;
	int		iter;

	iter = -1;
	if (str == NULL)
		return (NULL);
	cpy = ft_strdup(str);
	tmp = ft_strdup(str);
	while (1)
	{
		div = expand_div(&iter, tmp, env);
		free(tmp);
		if (iter == -2)
			break ;
		tmp = ft_strdup(div);
		free(div);
		div = NULL;
	}
	if (str && iter != 1 && (int)ft_strlen(str) != 0
		&& ft_strncmp(str, cpy, ft_strlen(cpy)) != 0)
		free(str);
	free(cpy);
	return (div);
}

// int main(int argc, char *argv[], char *envp[])
// {
//     char *test_strings[] = {
//         "Hello $USER, welcome to $HOME",
//         "$PATH",
//         "No variables here",
//         "$UNDEFINED_VAR",
//         "Mixed $USER and plain text",
//         NULL
//     };

//     for (int i = 0; test_strings[i] != NULL; i++)
//     {
//         printf("Original: %s\n", test_strings[i]);
//         char *expanded = ft_expander(envp, test_strings[i]);
//         if (expanded != NULL)
//         {
//             printf("Expanded: %s\n", expanded);
//             free(expanded);
//         }
//         else
//         {
//             printf("Expansion failed or returned NULL\n");
//         }
//         printf("\n");
//     }

//     return 0;
// }