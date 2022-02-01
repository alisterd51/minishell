/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 00:46:40 by anclarma          #+#    #+#             */
/*   Updated: 2022/01/29 14:41:21 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

int	ft_heredoc(int fd, char const *terminat)
{
	char	*line;

	line = NULL;
	while (get_next_line(STDIN_FILENO, &line) > 0 && ft_strcmp(terminat, line))
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = NULL;
	}
	free(line);
	line = NULL;
	return (0);
}
