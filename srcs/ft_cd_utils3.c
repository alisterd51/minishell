/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 03:52:18 by anclarma          #+#    #+#             */
/*   Updated: 2022/01/03 03:45:13 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** to_relative
*/
char	*to_relative(char *curpath, char *operand)
{
	(void)curpath;
	(void)operand;
	return (curpath);
}

/*
** ft_getenv
*/
char	*ft_getenv(char *key)
{
	(void)key;
	return (ft_strdup(""));
}

/*
** ft_setenv
*/
void	ft_setenv(char *key, char *value)
{
	(void)key;
	(void)value;
}

char	*pwd_p(void)
{
	return (NULL);
}
