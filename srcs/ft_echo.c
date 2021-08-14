/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 18:08:03 by anclarma          #+#    #+#             */
/*   Updated: 2021/08/14 19:10:07 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
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

int	ft_echo(int ac, char **av)
{
	int	newline;

	newline = 1;
	while (ac > 0 && valid_option("neE", *av))
	{
		if (ft_strchr(*av, 'n'))
			newline = 0;
		ac--;
		av++;
	}
	while (ac > 0)
	{
		write(1, *av, ft_strlen(*av));
		if (ac > 1)
			write(1, " ", 1);
		ac--;
		av++;
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}
