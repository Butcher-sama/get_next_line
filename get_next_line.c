/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkasap <fkasap@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:10:10 by fkasap            #+#    #+#             */
/*   Updated: 2024/11/28 17:21:57 by fkasap           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*fill_line(char *remainder)
{
	char	*line_copy; //kopyalanacak line
	size_t	i;

	i = 0;
	if (!remainder)
		return (NULL);

	while (remainder[i] && remainder[i] != '\n') //bittiği yeri || \n yerini bul
		i++;

	if (remainder[i] == '\n') // /n ile bitiyorsa line oluşturma
		line_copy = ft_substr(remainder, 0, (i + 1));
	if (remainder[i] == '\0') // /0 ile bitiyorsa line oluşturma
		line_copy = ft_substr(remainder, 0, i);

	return (line_copy);
}

static char	*update_remainder(char *remainder)
{
	char	*new_line;
	char	*new_reminder;

	if (!remainder)
		return (NULL);
	
	new_line = ft_strchr(remainder, '\n'); //yeni line başlangıç noktası tutma
	if (!new_line)
	{
		free (remainder);
		return (NULL);
	}

	new_reminder = ft_substr(remainder, (new_line - remainder + 1), ft_strlen(new_line + 1));
	//new_reminder = ft_strdup(new_line + 1); // yeni yeri yeni remaindera ver

	free (remainder); //eskisini serbest bırak
	return (new_reminder);
}

char	*get_next_line(int fd)
{
	char			buffer[BUFFER_SIZE + 1];
	ssize_t			bytes_Read;
	static char		*remainder;
	char			*line;
	char			*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while ((bytes_Read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[bytes_Read] = '\0';
		temp = remainder;
		remainder = remainder ? ft_strjoin(remainder, buffer) : ft_substr(buffer, 0, ft_strlen(buffer));
		free(temp);
		if (ft_strchr(remainder, '\n'))
			break;
	}
	if (bytes_Read < 0 || (!bytes_Read && (!remainder || !*remainder)))
	{
		free (remainder);
		return (NULL);
	}
	line = fill_line(remainder);
	remainder = update_remainder(remainder);
	return (line);
}
