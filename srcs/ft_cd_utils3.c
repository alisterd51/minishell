/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 03:52:18 by anclarma          #+#    #+#             */
/*   Updated: 2022/01/04 07:00:30 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
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

char	*pwd_p(void)
{
	return (alloc_pwd());
}
