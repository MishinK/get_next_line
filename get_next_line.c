/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashea <ashea@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 13:10:05 by ashea             #+#    #+#             */
/*   Updated: 2020/05/29 15:34:07 by ashea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char		*buffer;
	int				endbuffer;
	int				flag;

	if (fd < 0 || !line || BUFFER_SIZE < 1 || (*line = ft_strdup("")) == NULL)
		return (-1);
	if (buffer != NULL)
		if ((flag = ft_record(&buffer, line, ft_strlen(buffer))) != 0)
			return (flag);
	free(buffer);
	buffer = NULL;
	if ((buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))) == NULL)
		return (ft_clean(&buffer, line));
	if (read(fd, buffer, 0) < 0)
		return (ft_clean(&buffer, line));
	while ((endbuffer = read(fd, buffer, BUFFER_SIZE)) > 0)
		if ((flag = ft_record(&buffer, line, endbuffer)) != 0)
			return (flag);
	free(buffer);
	buffer = NULL;
	return (0);
}
