/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 18:08:03 by anclarma          #+#    #+#             */
/*   Updated: 2021/08/31 00:59:31 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"

int	ft_exit(int ac, char **av)
{
	ft_putendl_fd("exit", 1);
	if (ac == 1)
	{
		exit(0);//
		return (0);
	}
	else
	{
		ft_putstr_fd("exit: ", 2);
		ft_putendl_fd(strerror(E2BIG), 2);
		return (1);
	}
	//cas 0: aucun argument
	//	exit 0
	//cas 1: 1 arg et argument[0] numerique (signed long long)
	//	exit value (unsigned char)
	//cas 2: argument[0] non numerique
	//	exit 2 et affichache msg d'erreur
	//cas 3: 2 ou + arg et argument[0] numerique
	//	return 1 et affichage d'erreur
}
