/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 04:47:50 by anclarma          #+#    #+#             */
/*   Updated: 2022/02/05 06:49:11 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	ft_env(t_list *env, int *fd)
{
	while (env)
	{
		ft_putendl_fd(env->content, fd[1]);
		env = env->next;
	}
	return (0);
}
