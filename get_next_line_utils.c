/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkasap <fkasap@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:10:48 by fkasap            #+#    #+#             */
/*   Updated: 2024/12/09 13:42:17 by fkasap           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*ft_strjoin(char *s1, char *s2)
{
	char	*stogether;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
	{
		s1 = malloc(1);
		s1[0] = '\0';
	}
	stogether = (char *)malloc((ft_strlen(s1)
				+ ft_strlen(s2) + 1) * sizeof(char));
	if (!stogether)
		return (NULL);
	while (s1[j] != '\0')
		stogether[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0')
		stogether[i++] = s2[j++];
	stogether[i] = '\0';
	free (s1);
	return (stogether);
}

void	*ft_free(char **remainder)
{
	if (!*remainder)
	{
		return (NULL);
	}
	free (*remainder);
	*remainder = NULL;
	return (NULL);
}
