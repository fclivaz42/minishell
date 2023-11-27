/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclivaz <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:27:34 by fclivaz           #+#    #+#             */
/*   Updated: 2023/11/22 17:10:30 by fclivaz          ###    LAUSANNE.CH      */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*ft_gnljoin(char *s1, char *s2)
{
	int		i;
	int		diff;
	char	*ret;

	i = -1;
	diff = -1;
	if (s1 == NULL)
		s1 = (char *)ft_calloc(1, 1);
	if (!s1 || !s2)
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	ret = (char *)ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	while (s1[++diff] != 0)
		ret[diff] = s1[diff];
	while (s2[++i] != 0)
		ret[diff + i] = s2[i];
	ret[diff + i] = 0;
	free(s1);
	return (ret);
}

static char	*ft_copy(const char *s, const char *end)
{
	int		x;
	int		delta;
	char	*ret;

	x = -1;
	delta = (char *)end - (char *)s;
	ret = ft_calloc(delta + 1, sizeof(char));
	while (s[++x] && s[x] != '\n')
		ret[x] = s[x];
	if (s[x] == '\n')
		ret[x] = '\n';
	return (ret);
}

static char	*gnl_copy(int fd, char *raw)
{
	char	*buf;
	ssize_t	bytes;

	buf = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	bytes = 1;
	while (!ft_strchr(raw, '\n') && bytes != 0)
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

static void	*freeturn(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char		*stat;
	char			*rtrn;
	char			*tmp1;
	char			*tmp2;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	stat = gnl_copy(fd, stat);
	if (!stat)
		return (NULL);
	if (stat[0] == 0)
		return (freeturn(&stat));
	tmp1 = ft_strchr(stat, '\n');
	if (!tmp1)
	{
		tmp1 = ft_strdup(stat);
		freeturn(&stat);
		return (tmp1);
	}
	++tmp1;
	rtrn = ft_copy(stat, tmp1);
	tmp2 = ft_strdup(tmp1);
	free(stat);
	stat = tmp2;
	return (rtrn);
}
