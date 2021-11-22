/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_solve_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 22:24:39 by anclarma          #+#    #+#             */
/*   Updated: 2021/11/22 13:06:35 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "builtin.h"
#include "minishell.h"

int	main(int ac, char **av)
{
	char	*sol;

	if (ac != 2)
		return (1);
	sol = solve_path(getenv("PATH"), av[1]);
	ft_putendl_fd(sol, 1);
	free(sol);
	return (0);
}
