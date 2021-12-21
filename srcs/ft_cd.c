/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 03:52:18 by anclarma          #+#    #+#             */
/*   Updated: 2021/12/21 15:23:22 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int	ft_cd(int ac, char **av, t_list **env)
{
	int	ret;

	(void)env;
	ret = 0;
	if (ac > 2)
	{
		ft_putendl_fd("cd: trop d'arguments", 2);
		ret = 1;
	}
	else if (ac == 2)
		ret = chdir(av[1]);
	if (ret != 0)
		ret = 1;
	return (ret);
}
