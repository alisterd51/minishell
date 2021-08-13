/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 04:27:17 by anclarma          #+#    #+#             */
/*   Updated: 2021/08/13 04:35:34 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = -1;
	while (++i < len)
		*((unsigned char *)b + i) = (unsigned char)c;
	return (b);
}
