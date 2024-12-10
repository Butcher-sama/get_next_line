/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkasap <fkasap@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:14:44 by fkasap            #+#    #+#             */
/*   Updated: 2024/12/09 14:19:17 by fkasap           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char		*remainder[4096];
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (ft_free(&remainder[fd]));
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		if (remainder[fd])
			remainder[fd] = ft_strjoin(remainder[fd], buffer);
		else
			remainder[fd] = ft_substr(buffer, 0, ft_strlen(buffer));
		if (ft_strchr(remainder[fd], '\n'))
			break ;
	}
	if (bytes_read < 0 || (!bytes_read && (!remainder[fd] || !*remainder[fd])))
		return (ft_free(&remainder[fd]));
	line = fill_line(remainder[fd]);
	remainder[fd] = update_remainder(remainder[fd]);
	return (line);
}
