/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 04:38:18 by anclarma          #+#    #+#             */
/*   Updated: 2021/08/13 04:48:58 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	ssize_t	ret;

	if (!s)
		return ;
	ret = write(fd, s, ft_strlen(s));
	ret = write(fd, "\n", 1);
	(void)ret;
}
