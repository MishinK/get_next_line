/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashea <ashea@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 13:10:05 by ashea             #+#    #+#             */
/*   Updated: 2020/05/29 15:34:24 by ashea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int					ft_clean(char **buffer, char **line)
{
	free(*line);
	*line = NULL;
	free(*buffer);
	*buffer = NULL;
	return (-1);
}

int					ft_record(char **buffer, char **line, int endbuffer)
{
	char			*end;
	char			*buffer_copy;

	(*buffer)[endbuffer] = '\0';
	end = ft_strchr(*buffer, '\n');
	if (end)
	{
		*line = ft_strljoin(*line, *buffer, ft_strlen(*line) + (end - *buffer));
		buffer_copy = *buffer;
		*buffer = ft_strdup(end + 1);
		free(buffer_copy);
		buffer_copy = NULL;
		if (*line == NULL || *buffer == NULL)
			return (ft_clean(buffer, line));
		return (1);
	}
	*line = ft_strljoin(*line, *buffer, ft_strlen(*line) + BUFFER_SIZE);
	if (*line == NULL)
		return (ft_clean(buffer, line));
	return (0);
}

int					get_next_line(int fd, char **line)
{
	static char		*buffer[1025];
	int				endbuffer;
	int				flag;

	if (fd < 0 || !line || BUFFER_SIZE < 1 || (*line = ft_strdup("")) == NULL)
		return (-1);
	if (buffer[fd] != NULL)
		if ((flag = ft_record(&(buffer[fd]), line, ft_strlen(buffer[fd]))) != 0)
			return (flag);
	free(buffer[fd]);
	buffer[fd] = NULL;
	if ((buffer[fd] = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))) == NULL)
		return (ft_clean(&(buffer[fd]), line));
	if (read(fd, buffer[fd], 0) < 0)
		return (ft_clean(&(buffer[fd]), line));
	while ((endbuffer = read(fd, buffer[fd], BUFFER_SIZE)) > 0)
		if ((flag = ft_record(&(buffer[fd]), line, endbuffer)) != 0)
			return (flag);
	free(buffer[fd]);
	buffer[fd] = NULL;
	return (0);
}
