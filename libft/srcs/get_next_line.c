/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:27:34 by fclivaz           #+#    #+#             */
/*   Updated: 2023/02/15 20:59:44 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*gnl_skip(char *line)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	if (!line)
		return (NULL);
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	str = (char *)ft_calloc((ft_gnllen(line) - i + 1), sizeof(char));
	j = 0;
	while (line[i])
		str[j++] = line[i++];
	str[j] = 0;
	if (str[0] == 0)
	{
		free(str);
		free(line);
		return (NULL);
	}
	free(line);
	return (str);
}

static char	*gnl_ret(const char *str)
{
	char			*dst;
	int				i;

	i = 0;
	if (!str)
		return (NULL);
	if (str[0] == 0)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	dst = (char *)ft_calloc((i + 2), sizeof(char));
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		dst[i] = str[i];
	i++;
	}
	if (str[i] == '\n')
		dst[i] = '\n';
	dst[i + 1] = 0;
	return (dst);
}

static char	*gnl_copy(int fd, char *raw)
{
	char	*buf;
	ssize_t	bytes;

	buf = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	bytes = 1;
	while (!ft_gnlchr(raw, '\n') && bytes != 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes == 0)
			break ;
		if (bytes < 0)
		{
			free(raw);
			free(buf);
			return (NULL);
		}
		buf[bytes] = 0;
		raw = ft_gnljoin(raw, buf);
	}
	free(buf);
	return (raw);
}

char	*get_next_line(int fd)
{
	static char		*stat;
	char			*rtrn;

	if (fd < 0)
		return (NULL);
	if (BUFFER_SIZE < 0)
		return (NULL);
	stat = gnl_copy(fd, stat);
	if (!stat)
		return (NULL);
	rtrn = gnl_ret(stat);
	stat = gnl_skip(stat);
	return (rtrn);
}
