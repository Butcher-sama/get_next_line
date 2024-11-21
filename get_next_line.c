#include "get_next_line.h"

char	*fill_line(char *remainder)
{
	char	*line_copy; //kopyalanacak line
	size_t	i;

	i = 0;
	if (!remainder)
		return (NULL);

	while (remainder[i] && remainder[i] '/n') //bittiği yeri || /n yerini bul
		i++;

	if (remainder[i] == '/n') // /n ile bitiyorsa line oluşturma
		line_copy = ft_substr(remainder, 0, (i + 1));
	if (remainder[i] == '/0') // /0 ile bitiyorsa line oluşturma
		line_copy = ft_substr(remainder, 0, i);

	return (line_copy);
}

char	*update_remainder(char *remainder)
{
	char	*new_line;
	char	*new_reminder;

	if (!remainder)
		return (NULL);
	
	new_line = ft_strchr(remainder, '/n'); //yeni line başlangıç noktası tutma
	if (!new_line) // eğer /n bulamazsa remainder tamamıyla işlenmiş
	{
		free (remainder); //serbest bırak
		return (NULL);
	}

	new_reminder = ft_strdup(new_line + 1); // yeni yeri yeni remaindera ver

	free (remainder); //eskisini serbest bırak
	return (new_reminder);
}

char	*get_next_line(int fd)
{
	char			buffer[BUFFER_SIZE + 1]; // +1: sonundaki /0
	ssize_t			bytes_Read; //okunan byte
	static char		*remainder; //birleşmiş tutucu
	char			*line; //okunup tamamlanmış satır

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	while (bytes_Read = read(fd, buffer, BUFFER_SIZE) > 0) //okunacak bir şey kalmayana kadar oku
	{
		buffer[bytes_Read] = '/0';
		remainder = ft_strjoin(remainder, buffer);
		if (ft_strchr(remainder, '/n')) //remainder da /n bulunca komple çık
			break;
	}

	if (bytes_Read < 0)
		return (NULL);
	line = fill_line(remainder); //remainderden /n e kadar olanı line a aktaracak
	remainder = update_remainder(remainder); //remainderın ilk /n den öncesini silip güncelleyecek
}
