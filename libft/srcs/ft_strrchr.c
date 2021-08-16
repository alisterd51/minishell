/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 23:54:52 by anclarma          #+#    #+#             */
/*   Updated: 2021/08/16 17:02:57 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*dst;

	if (!s)
		return (NULL);
	dst = NULL;
	if (!*s && !c)
		return ((char *)s);
	if (!c)
		return ((char *)s + ft_strlen(s));
	while (*s)
	{
		if (*s == c)
			dst = (char *)s;
		++s;
	}
	return (dst);
}
