/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szawi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 10:36:03 by szawi             #+#    #+#             */
/*   Updated: 2021/11/19 10:36:07 by szawi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main(int ac, char *av[])
{
	char	*line;
	int		ret;
	int		fd;

	if (ac != 2)
		return (0);
	fd = open(av[1], O_RDONLY);
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
