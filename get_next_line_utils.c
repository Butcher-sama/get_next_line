#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strchr(const char *src, int c)
{
	unsigned int	i;
	char			ch;

	ch = (char) c;
	i = 0;
	while (src[i] != '\0')
	{
		if (src[i] == ch)
		{
			return ((char *)&src[i]);
		}
		i++;
	}
	if (ch == '\0')
		return ((char *)&src[i]);
	return (NULL);
}

char	*ft_strdup(const char *s1)
{
	char	*starget;
	size_t	count;

	count = ft_strlen(s1);
	starget = (char *)malloc((count + 1) * sizeof(char));
	if (!starget)
		return (NULL);
	ft_strlcpy(starget, s1, count + 1);
	starget[count] = '\0';
	return (starget);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	slen;
	char	*substring;

	i = 0;
	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (slen < start)
		return (malloc(sizeof(char)));
	if (len > slen - start)
		len = slen - start;
	substring = (char *)malloc((len + 1) * sizeof(char));
	if (!substring)
		return (NULL);
	while (i < len)
	{
		substring[i] = s[start];
		i++;
		start++;
	}
	substring[i] = '\0';
	return (substring);
}
