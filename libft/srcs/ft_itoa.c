/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 17:31:02 by anclarma          #+#    #+#             */
/*   Updated: 2022/02/04 18:10:21 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	size_itoa(int n)
{
	size_t	size;

	size = 0;
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

static unsigned int	ft_abs(int n)
{
	if (n > 0)
		return ((unsigned int)n);
	else
		return ((unsigned int)(n * -1));
}

char	*ft_itoa(int n)
{
	char	buf[12];
	size_t	i;
	size_t	size;

	if (n == 0)
		return (ft_strdup("0"));
	ft_bzero(buf, 12);
	i = 0;
	if (n < 0)
		buf[i++] = '-';
	size = size_itoa(n);
	while (size > 0)
	{
		buf[i + size - 1] = ft_abs(n) % 10 + '0';
		n /= 10;
		size--;
	}
	return (ft_strdup(buf));
}
