/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 04:57:17 by anclarma          #+#    #+#             */
/*   Updated: 2021/08/13 01:59:55 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>
#include "libft.h"

static int	ft_error(const char *name, const char *error)
{
	write(2, name, ft_strlen(name));
	write(2, ": ", 2);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	return (1);
}

int	ft_pwd(int ac, char **av)
{
	char	*buf;
	size_t	size;

	(void)ac;
	(void)av;
	if (ac > 0)
		return (ft_error("pwd", "too many arguments"));
	size = 1;
	buf = malloc(size);
	if (!buf)
		return (ft_error("pwd", strerror(errno)));
	while (!getcwd(buf, size))
	{
		size *= 2;
		if (errno != ERANGE)
			return (ft_error("pwd", strerror(errno)));
		else if (size == 0)
			return (ft_error("pwd", strerror(EOVERFLOW)));
		buf = realloc(buf, size);
		if (!buf)
			return (ft_error("pwd", strerror(errno)));
	}
	ft_putendl_fd(buf, 1);
	free(buf);
	return (0);
}
