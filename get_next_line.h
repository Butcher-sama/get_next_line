#ifndef	GET_NEXT_LINE
# define GET_NEXT_LINE

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
# endif

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

char	*fill_line(char *remainder);
char	*update_remainder(char *remainder);
char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *src, int c);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
