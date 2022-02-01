/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 23:02:47 by anclarma          #+#    #+#             */
/*   Updated: 2022/01/27 23:35:51 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include "libft.h"

int	get_next_line(int fd, char **line)
{
	ssize_t	ret;
	char	*str;
	char	*tmp;
	char	buf[2];

	ret = read(fd, buf, 1);
	buf[1] = '\0';
	if (ret <= 0)
		return ((int)ret);
	str = ft_strdup("");
	if (!str)
		return (-1);
	while (ret > 0 && buf[0] != '\n')
	{
		tmp = str;
		str = ft_strjoin(tmp, buf);
		if (!str)
			return (-1);
		free(tmp);
		ret = read(fd, buf, 1);
	}
	*line = str;
	return (1);
}
