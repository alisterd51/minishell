/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 04:47:50 by anclarma          #+#    #+#             */
/*   Updated: 2021/08/15 05:01:33 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	ft_env(int ac, char **av)
{
	char	*env_var;

	(void)ac;
	(void)av;
	env_var = getenv("TERM_PROGRAM");
	ft_putstr_fd("TERM_PROGRAM", 1);
	ft_putstr_fd("=", 1);
	ft_putendl_fd(env_var, 1);
	return (0);
}
