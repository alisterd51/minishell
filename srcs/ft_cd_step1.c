/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_step1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 03:52:18 by anclarma          #+#    #+#             */
/*   Updated: 2022/01/04 08:19:33 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>

int	step0(t_cd *cd_arg)
{
	if (cd_arg->operand == NULL && !test_home(*cd_arg->env))
		return (10);
	return (1);
}

int	step1(t_cd *cd_arg)
{
	if (cd_arg->operand == NULL && test_home(*cd_arg->env))
		cd_arg->operand = ft_getenv("HOME=", *cd_arg->env);
	return (2);
}

int	step2(t_cd *cd_arg)
{
	if (cd_arg->operand[0] == '/')
	{
		cd_arg->curpath = ft_strdup(cd_arg->operand);
		return (6);
	}
	return (3);
}

int	step3(t_cd *cd_arg)
{
	if (test_dot(cd_arg->operand) || test_dotdot(cd_arg->operand))
		return (5);
	return (4);
}

int	step4(t_cd *cd_arg)
{
	char	*subcdpath;
	char	*cdpath;
	char	*concatenation;

	cdpath = ft_getenv("CDPATH=", *cd_arg->env);
	if (cdpath == NULL)
		cdpath = "";
	subcdpath = get_subcdpath(cdpath);
	while (subcdpath != NULL)
	{
		concatenation = ft_concatenation(subcdpath, "/", cd_arg->operand);
		if (test_directory(concatenation))
		{
			cd_arg->curpath = concatenation;
			return (6);
		}
		subcdpath = get_subcdpath(cdpath);
	}
	return (5);
}
