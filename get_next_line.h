/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szawi <szawi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 17:21:02 by szawi             #+#    #+#             */
/*   Updated: 2021/11/10 17:21:02 by szawi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <fcntl.h>

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

int get_next_line(int fd, char **line);

# define BUFFER_SIZE 10

// to check:
// - when buffer_size < 4
// - last \n

#endif
