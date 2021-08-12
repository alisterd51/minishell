/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 04:56:56 by anclarma          #+#    #+#             */
/*   Updated: 2021/08/12 05:29:08 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static int	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

static int	check_flag(const char *flag, const char *allowed)
{
	if (!flag || !allowed)
		return (0);
	if (*flag != '-')
		return (0);
	flag++;
	while (*flag)
	{
		if (*flag != *allowed)
			return (0);
		flag++;
	}
	return (1);
}

int	ft_echo(int ac, char **av)
{
	int	newline;

	newline = 1;
	if (ac > 0 && check_flag(*av, "n"))
	{
		newline = 0;
		av++;
		ac--;
	}
	while (ac > 0)
	{
		write (1, *av, ft_strlen(*av));
		av++;
		ac--;
		if (ac > 0)
			write(1, " ", 1);
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}
