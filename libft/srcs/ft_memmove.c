/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 04:25:58 by anclarma          #+#    #+#             */
/*   Updated: 2021/11/10 22:27:52 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	if (dst < src)
	{
		while (i < len)
		{
			*((unsigned char *)dst + i) = *((unsigned char *)src + i);
			i++;
		}
	}
	else if (src < dst)
		while (0 < len--)
			*((unsigned char *)dst + len) = *((unsigned char *)src + len);
	return (dst);
}
