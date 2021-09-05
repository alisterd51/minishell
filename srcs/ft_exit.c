/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 18:08:03 by anclarma          #+#    #+#             */
/*   Updated: 2021/09/05 16:08:03 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_strisnum(char *str)
{
	if (!str)
		return (0);
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		str++;
	if (!ft_isdigit(*str))
		return (0);
	while (ft_isdigit(*str))
		str++;
	while (ft_isspace(*str))
		str++;
	if (*str != '\0')
		return (0);
	return (1);
}

int	ft_exit(int ac, char **av, int status)
{
	ft_putendl_fd("exit", 1);
	if (ac == 0)
	{
		exit(status);
		return (0);
	}
	else if (!ft_strisnum(av[0]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(av[0], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(255);
		return (1);
	}
	else if (ac > 1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putendl_fd("too many arguments", 2);
		return (1);
	}
	else
		return (ft_atoi(av[0]));
}
