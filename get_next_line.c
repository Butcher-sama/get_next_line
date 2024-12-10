/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkasap <fkasap@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:10:10 by fkasap            #+#    #+#             */
/*   Updated: 2024/12/09 14:27:03 by fkasap           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*fill_line(char *remainder)
{
	char	*line_copy;
	size_t	i;

	i = 0;
	if (!remainder)
		return (NULL);
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (remainder[i] == '\n')
		line_copy = ft_substr(remainder, 0, (i + 1));
	if (remainder[i] == '\0')
		line_copy = ft_substr(remainder, 0, i);
	if (!line_copy)
		return (ft_free(&remainder));
	return (line_copy);
}

static char	*update_remainder(char *remainder)
{
	char	*new_line;
	char	*new_reminder;

	if (!remainder)
		return (ft_free(&remainder));
	new_line = ft_strchr(remainder, '\n');
	if (!new_line)
		return (ft_free(&remainder));
	new_reminder = ft_substr(remainder, (new_line - remainder + 1),
			ft_strlen(new_line + 1));
	if (!new_reminder)
		return (ft_free(&remainder));
	ft_free(&remainder);
	return (new_reminder);
}

char	*get_next_line(int fd)
{
	char			buffer[BUFFER_SIZE + 1];
	ssize_t			bytes_read;
	static char		*remainder;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (ft_free(&remainder));
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		if (remainder)
			remainder = ft_strjoin(remainder, buffer);
		else
			remainder = ft_substr(buffer, 0, ft_strlen(buffer));
		if (ft_strchr(remainder, '\n'))
			break ;
	}
	if (bytes_read < 0 || (!bytes_read && (!remainder || !*remainder)))
		return (ft_free(&remainder));
	line = fill_line(remainder);
	remainder = update_remainder(remainder);
	return (line);
}
