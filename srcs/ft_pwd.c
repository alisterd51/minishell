/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 18:08:03 by anclarma          #+#    #+#             */
/*   Updated: 2021/08/15 02:58:58 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/errno.h>
#include "libft.h"

static int	valid_option(const char *option, char *arg)
{
	if (arg[0] != '-' || arg[1] == '\0')
		return (0);
	arg++;
	while (*arg)
	{
		if (!ft_strchr(arg, *option))
			return (0);
		arg++;
	}
	return (1);
}

static char	*alloc_pwd(void)
{
	char	*buf;
	size_t	size;

	size = 1;
	buf = (char *)malloc(size);
	if (!buf)
		return (NULL);
	while (!getcwd(buf, size))
	{
		if (errno != ERANGE)
		{
			free(buf);
			return (NULL);
		}
		else if (size == 0)
		{
			free(buf);
			return (NULL);
		}
		size *= 2;
		buf = (char *)ft_realloc(buf, size);
		if (!buf)
			return (NULL);
	}
	return (buf);
}

int	ft_pwd(int ac, char **av)
{
	char	*buf;

	while (ac > 0 && valid_option("LP", *av))
	{
		ac--;
		av++;
	}
	buf = alloc_pwd();
	if (!buf)
	{
		ft_putstr_fd("pwd: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	ft_putendl_fd(buf, 1);
	free(buf);
	return (0);
}
