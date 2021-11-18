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

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str && *str++)
		len++;
	return (len);
}

int		ft_newline(const char *all)
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

int		ft_strjoin(char *from, char **to, int c)
{
	char	*new;
	int		i;
	int		j;

	new = malloc(ft_strlen(from) + ft_strlen(*to) + 1);
	if (!new)
		return (0);
	i = 0;
	j = 0;
	while (*to && (*to)[j])
		new[i++] = (*to)[j++];
	j = 1;
	if (from && from[0])
		new[i++] = from[0];
	while (from[j] && from[j - 1] != c)
		new[i++] = from[j++];
	new[i] = 0;
	if (*to)
		free(*to);
	*to = new;
	return (1);
}

int		ft_clear_all(char **all, char **line, int ret)
{
	int		i;
	int		check;
	char	*new;

	i = 1;
	new = NULL;
	while ((*all)[i - 1] != '\n')
		i++;
	check = ft_strjoin(*all, line, '\n');
	if (check && (*all)[i])
		check = ft_strjoin(&(*all)[i], &new, 0);
	if (check)
	{
		if (*all)
			free(*all);
		*all = NULL;
		if (new)
			*all = new;
		else if (!*all && !ret)
			return (0);
	}
	else
		return (-1);
	return (1);
}

int		get_next_line(int fd, char **line)
{
	int			ret;
	int			check;
	char		buff[BUFFER_SIZE];
	static char *all;

	*line = NULL;
	ret = read(fd, buff, BUFFER_SIZE);
	buff[ret] = 0;
	if (ret < 0)
		return (ret);
	if (ret > 0)
	{
		check = ft_strjoin(buff, &all, 0);
		if (!check)
		{
			if (all)
				free(all);			
			return (-1);
		}
		else if (!ft_newline(all))
			return (get_next_line(fd, line));
	}
	return (ft_clear_all(&all, line, ret));
}

int		main(void)
{
	char	*line;
	int		ret;
	int		fd;

	fd = open("get_next_line.h", O_RDONLY);
	ret = get_next_line(fd, &line);
	while (ret > 0)
	{
		printf("%s", line);
		if (line)
			free(line);
		ret = get_next_line(fd, &line);
	}
	printf("%s", line);
	if (line)
		free(line);
	close(fd);
	return (0);
}
