/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szawi <szawi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 17:17:35 by szawi             #+#    #+#             */
/*   Updated: 2021/11/10 17:17:35 by szawi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// work very good, but don't read last line

static size_t	ft_strlen(const char *str, int c)
{
	size_t	len;

	len = 0;
	while (str && *str && *str != c)
	{
		len++;
		str++;
	}
	return (len);
}

static int	ft_newline(const char *all)
{
	int	i;

	i = 0;
	while (all && all[i])
	{
		if (all[i++] == '\n')
			return (1);
	}
	return (0);
}

static char	*ft_strjoin(char *from, char *to, int c)
{
	char	*new;
	int		i;
	int		j;

	new = malloc(ft_strlen(from, c) + ft_strlen(to, 0) + 1);
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (to && to[j])
		new[i++] = to[j++];
	j = 0;
	while (from && from[j] && from[j] != c)
		new[i++] = from[j++];
	new[i] = 0;
	return (new);
}

static int	ft_clear_all(char **all, char **line, int ret)
{
	char	*new;
	int		i;

	i = 0;
	new = NULL;
	*line = ft_strjoin(*all, *line, '\n');
	while (*all && (*all)[i] && (*all)[i] != '\n')
		i++;
	if (*all && (*all)[i] && (*all)[i + 1])
		new = ft_strjoin(&(*all)[++i], NULL, 0);
	if (*all)
		free(*all);
	*all = new;
	if (!ret && !(*all))
		return (0);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	int			ret;
	char		buff[BUFFER_SIZE + 1];
	char		*new;
	static char	*all;

	if (BUFFER_SIZE < 1)
		return (-1);
	*line = NULL;
	ret = read(fd, buff, BUFFER_SIZE);
	buff[ret] = 0;
	if (ret < 0)
		return (ret);
	if (ret > 0)
	{
		new = ft_strjoin(buff, all, 0);
		if (all)
			free(all);
		all = new;
		if (!all)
			return (-1);
		else if (!ft_newline(all))
			return (get_next_line(fd, line));
	}
	return (ft_clear_all(&all, line, ret));
}
