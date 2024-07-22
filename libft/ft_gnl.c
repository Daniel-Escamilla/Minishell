/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:28:59 by sergio            #+#    #+#             */
/*   Updated: 2024/07/05 15:16:01 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static char	*buffer_remainder(char *buff)
{
	int		i;
	int		j;
	char	*buff_rema;

	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (buff[i] == '\n')
		i++;
	buff_rema = (char *)ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (buff_rema == NULL)
	{
		free(buff);
		return (NULL);
	}
	j = 0;
	while (buff[i] != '\0')
		buff_rema[j++] = buff[i++];
	free(buff);
	buff = NULL;
	return (buff_rema);
}

static char	*take_line(char *buff)
{
	int		i;
	char	*line;

	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (buff[i] == '\n')
		i++;
	line = (char *)ft_calloc((i + 1), sizeof(char));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (buff [i] && buff[i] != '\n')
	{
		line[i] = buff[i];
		i++;
	}
	if (buff[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	return (line);
}

static char	*read_until_nl(int fd, char *buff, char *temp)
{
	ssize_t	num_bytes;

	while (ft_strchr(buff, '\n') == NULL)
	{
		num_bytes = read(fd, buff, BUFFER_SIZE);
		if (num_bytes < 0)
		{
			free (temp);
			temp = NULL;
			return (NULL);
		}
		if (num_bytes == 0)
			return (temp);
		buff[num_bytes] = '\0';
		temp = ft_strjoin(temp, buff);
		if (temp == NULL)
		{
			free (temp);
			return (NULL);
		}
	}
	return (temp);
}

static char	*read_buffer(int fd, char *buff)
{
	char	*temp;

	temp = NULL;
	if (buff == NULL)
	{
		buff = (char *)malloc(BUFFER_SIZE + 1);
		if (buff == NULL)
			return (NULL);
		ft_memset(buff, 0, BUFFER_SIZE + 1);
	}
	else
	{
		temp = ft_strjoin(temp, buff);
		if (temp == NULL)
			return (NULL);
	}
	temp = read_until_nl(fd, buff, temp);
	free (buff);
	buff = NULL;
	if (temp == NULL)
		return (NULL);
	return (temp);
}

char	*ft_gnl(int fd)
{
	static char	*buff;
	char		*line;

	buff = read_buffer(fd, buff);
	if (buff == NULL || *buff == '\0')
	{
		free(buff);
		buff = NULL;
		return (NULL);
	}
	line = take_line(buff);
	buff = buffer_remainder(buff);
	if (!buff)
		free(buff);
	return (line);
}
