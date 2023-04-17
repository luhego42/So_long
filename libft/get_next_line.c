/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhego <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 16:28:03 by luhego            #+#    #+#             */
/*   Updated: 2023/03/29 19:08:34 by luhego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_line_len(char *line)
{
	int	l;

	l = 0;
	while (line[l] && line[l] != '\n')
		l++;
	return (l + 1);
}

static char	*ft_gnl_substr(char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	s_len;

	if (s == NULL)
		return (0);
	s_len = ft_strlen(s);
	if (len > s_len - start)
		len = s_len - start;
	if (start >= s_len)
		return (ft_calloc(1, sizeof(char)));
	str = ft_calloc(len + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_strlcat(str, &s[start], len + 1);
	free(s);
	return (str);
}

static char	*read_line(int fd, char *stash)
{
	int		sizeofread;
	char	*line;

	line = ft_calloc(BUFFER_SIZE, sizeof(char));
	sizeofread = 1;
	if (stash)
		ft_strlcat(line, stash, BUFFER_SIZE);
	while (sizeofread > 0 && ft_strrchr(line, '\n') == NULL)
	{
		sizeofread = read(fd, stash, BUFFER_SIZE);
		stash[sizeofread] = '\0';
		if (sizeofread)
			line = ft_strjoin(line, stash);
		if (sizeofread < BUFFER_SIZE)
			break ;
	}
	if (sizeofread < 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	stash[BUFFER_SIZE + 1];
	char		*line;
	int			line_len;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = read_line(fd, stash);
	if (line == NULL || line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	line_len = ft_line_len(line);
	i = 0;
	while (line[line_len + i - 1])
	{
		stash[i] = line[line_len + i];
		i++;
	}
	stash[i] = '\0';
	line = ft_gnl_substr(line, 0, line_len);
	return (line);
}
