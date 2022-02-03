/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_step2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 03:52:18 by anclarma          #+#    #+#             */
/*   Updated: 2022/02/03 00:36:53 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include "minishell.h"

int	step5(t_cd *cd_arg)
{
	free(cd_arg->curpath);
	cd_arg->curpath = ft_strdup(cd_arg->operand);
	return (6);
}

int	step6(t_cd *cd_arg)
{
	char	*pwd;
	char	*concat;

	pwd = (char [1024]){0};
	if (test_option("-P"))
		return (9);
	if (cd_arg->curpath && cd_arg->curpath[0] != '/')
	{
		getcwd(pwd, 1024);
		if (pwd[ft_strlen(pwd) - 1] == '/')
			concat = ft_concatenation(pwd, "", cd_arg->curpath);
		else
			concat = ft_concatenation(pwd, "/", cd_arg->curpath);
		free(cd_arg->curpath);
		cd_arg->curpath = concat;
	}
	return (7);
}

int	step7(t_cd *cd_arg)
{
	char	*resolved_path;

	resolved_path = (char [PATH_MAX]){0};
	ft_realpath(cd_arg->curpath, resolved_path);
	free(cd_arg->curpath);
	cd_arg->curpath = ft_strdup(resolved_path);
	if (!cd_arg->curpath)
		return (10);
	return (8);
}

int	step8(t_cd *cd_arg)
{
	cd_arg->new_pwd = ft_strdup(cd_arg->curpath);
	if (ft_strlen(cd_arg->curpath) + 1 > PATH_MAX
		&& ft_strlen(cd_arg->operand) + 1 < PATH_MAX)
	{
		free(cd_arg->curpath);
		cd_arg->curpath = to_relative(cd_arg->curpath, cd_arg->operand);
	}
	return (9);
}

int	step9(t_cd *cd_arg)
{
	char	*pwd;
	char	oldpwd[1024];

	ft_setenv("OLDPWD=", getcwd(oldpwd, 1024), cd_arg->env);
	cd_arg->ret = chdir(cd_arg->curpath);
	if (!test_option("-P"))
		ft_setenv("PWD=", cd_arg->new_pwd, cd_arg->env);
	else
	{
		pwd = pwd_p();
		ft_setenv("PWD=", pwd, cd_arg->env);
		free(pwd);
	}
	return (10);
}
