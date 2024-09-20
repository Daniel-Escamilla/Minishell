/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:03:56 by descamil          #+#    #+#             */
/*   Updated: 2024/09/20 23:16:20 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	ft_free_fcheck_args(char **args1, char **args2)
{
	if (args1)
		ft_strstr_free(args1);
	ft_strstr_free(args2);
}

static char	**ft_change_args(char **args, int pos, int i, int j)
{
	char	**args1;
	char	**args2;
	char	**tmp;

	args1 = NULL;
	if (pos != 0)
		args1 = (char **)ft_calloc(sizeof(char *), pos + 1);
	while (i != pos)
		args1[j++] = ft_strdup(args[i++]);
	if (i == pos)
		args2 = ft_split_red(args[pos], 0);
	if (args1 != NULL)
		tmp = ft_strstr_join(args1, args2);
	else
		tmp = ft_strstr_join(args2, NULL);
	ft_free_fcheck_args(args1, args2);
	args1 = NULL;
	if (ft_strstr_len(args) - pos != 1)
		args1 = (char **)ft_calloc(sizeof(char *), ft_strstr_len(args) - pos);
	j = 0;
	while (ft_strstr_len(args) - pos > 1 && args[++i])
		args1[j++] = ft_strdup(args[i]);
	args2 = ft_strstr_join(tmp, args1);
	ft_free_fcheck_args(args1, tmp);
	return (args2);
}

void	ft_new_args(t_cmd *current, int *i)
{
	char	**args;

	args = ft_change_args(current->args, *i, 0, 0);
	if (ft_strstr_len(args) - ft_strstr_len(current->args) != 0)
		*i = ft_strstr_len(args) - ft_strstr_len(current->args) - 1;
	if (current->args)
		ft_strstr_free(current->args);
	current->args = ft_strstr_join(args, NULL);
	ft_strstr_free(args);
}
