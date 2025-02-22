/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:21:55 by descamil          #+#    #+#             */
/*   Updated: 2025/02/22 11:29:03 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static void	ft_insert_sorted(t_list **list, char *str)
{
	t_list	*current;
	t_list	*new_node;

	new_node = ft_lstnew(str);
	if (!new_node)
		return ;
	if (*list == NULL || ft_strncmp((char *)
			(*list)->content, str, ft_strlen(str)) > 0)
	{
		new_node->next = *list;
		*list = new_node;
		return ;
	}
	current = *list;
	while (current->next != NULL && ft_strncmp((char *)
			(current->next->content), str, ft_strlen(str)) < 0)
		current = current->next;
	new_node->next = current->next;
	current->next = new_node;
}

static void	ft_print_list(t_list *list)
{
	char	*env_var;
	char	*join;
	char	*var;
	size_t	size;

	while (list)
	{
		env_var = (char *)list->content;
		join = ft_strchr(env_var, '=') + 1;
		size = ft_strlen(env_var) - ft_strlen(join);
		var = ft_calloc(size + 1, sizeof(char));
		ft_strlcpy(var, env_var, size + 1);
		write(STDOUT_FILENO, "declare -x ", 12);
		write(STDOUT_FILENO, var, ft_strlen(var));
		write(STDOUT_FILENO, "\"", 1);
		write(STDOUT_FILENO, join, ft_strlen(join));
		write(STDOUT_FILENO, "\"", 1);
		write(STDOUT_FILENO, "\n", 1);
		free(var);
		list = list->next;
	}
}

int	ft_print_order(char **env)
{
	t_list	*list;
	char	**enviroment;
	int		i;

	i = 0;
	list = NULL;
	enviroment = ft_strstr_dup(env);
	while (enviroment[i])
		ft_insert_sorted(&list, enviroment[i++]);
	ft_print_list(list);
	ft_lstclear(&list, free);
	free(enviroment);
	return (0);
}
