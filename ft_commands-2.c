/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands-2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:35:49 by user              #+#    #+#             */
/*   Updated: 2024/09/17 15:08:50 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_position(char *input, int *size, int stop)
{
	int	i;
	int	pos;

	i = 0;
	pos = 0;
	while (stop-- != 0)
	{
		while (input[pos] == ' ')
			pos++;
		pos += size[i++];
	}
	while (input[pos] == ' ')
		pos++;
	return (pos);
}

char	*ft_inside_argv(char *input, int *size, int stop)
{
	char	*exit;
	int		i;
	int		pos;

	i = -1;
	exit = (char *)ft_calloc((size[stop]), sizeof(char));
	if (exit == NULL)
		return (NULL);
	pos = ft_position(input, size, stop);
	while (++i < size[stop] - 1)
		exit[i] = input[pos++];
	return (exit);
}

void	ft_plus_one(int value1, int value2)
{
	value1 += 1;
	value2 += 1;
}

int ft_size_argv(char *input, int stop, int size, int index)
{
	int start;

	size = 0;
	while (stop != -1 && input[index])
	{
		while (input[index] == ' ')
			index++;
		while (input[index] != ' ' && input[index] != '\0')
		{
			if (input[index] == '\'' || input[index] == '\"')
			{
				start = index;
				index = ft_locate_next_quote(index + 1, input, input[index]) + 1;
				size += index - start;
			}
			else
				ft_plus_one(size++, index++);
		}
		while (input[index] != '\0' && input[index] != ' ')
			ft_plus_one(size++, index++);
		stop--;
		if (stop != -1)
			size = 0;
	}
	return (++size);
}

int	*ft_sizes_input(char *input, int argc)
{
	int	*sizes;
	int	i;

	i = -1;
	sizes = (int *)ft_calloc(argc, sizeof(int));
	if (sizes == NULL)
		return (0);
	while (++i < argc - 1)
		sizes[i] = ft_size_argv(input, i, 0, 0);
	return (sizes);
}

void	ft_free(char **argv, int *size, char ***args)
{
	if (argv)
		ft_strstr_free(argv);
	if (size)
		free(size);
	*args = NULL;
}

void	ft_get_args(char *input, int argc, char ***args)
{
	char	**argv;
	int		*size;
	int		i;

	i = -1;
	argv = ft_calloc((argc + 2), sizeof(char *));
	if (argv == NULL)
        return (ft_free(NULL, NULL, args));
	size = ft_sizes_input(input, argc + 1);
	if (size == NULL)
		return (ft_free(argv, NULL, args));
	while (++i < argc)
	{
		argv[i] = ft_inside_argv(input, size, i);
		if (argv[i] == NULL)
			return (ft_free(argv, size, args));
	}
	argv[argc + 1] = NULL;
	free(size);
	*args = argv;
}
