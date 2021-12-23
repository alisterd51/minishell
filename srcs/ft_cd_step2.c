/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_step2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 03:52:18 by anclarma          #+#    #+#             */
/*   Updated: 2021/12/23 17:05:40 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <linux/limits.h>
#include <unistd.h>
#include "minishell.h"

int	step5(t_cd *cd_arg)
{
	cd_arg->curpath = cd_arg->operand;
	return (6);
}

int	step6(t_cd *cd_arg)
{
	char	*pwd;

	pwd = NULL;
	if (test_option("-P"))
		return (9);
	if (cd_arg->curpath[0] != '/')
	{
		pwd = ft_getenv("PWD");
		if (pwd[ft_strlen(pwd) - 1] == '/')
			cd_arg->curpath = ft_concatenation(pwd, "", cd_arg->curpath);
		else
			cd_arg->curpath = ft_concatenation(pwd, "/", cd_arg->curpath);
	}
	return (7);
}

int	step7(t_cd *cd_arg)
{
	cd_arg->curpath = clean_a(cd_arg->curpath);
	cd_arg->curpath = clean_b(cd_arg->curpath);
	cd_arg->curpath = clean_c(cd_arg->curpath);
	return (8);
}

//incomplet mais bon a priori
int	step8(t_cd *cd_arg)
{
	cd_arg->new_pwd = cd_arg->curpath;
	if (ft_strlen(cd_arg->curpath) + 1 > PATH_MAX
		&& ft_strlen(cd_arg->operand) + 1 < PATH_MAX)
		cd_arg->curpath = to_relative(cd_arg->curpath, cd_arg->operand);
	return (9);
}

//si erreur affichage message d'erreur et fin
int	step9(t_cd *cd_arg)
{
	cd_arg->ret = chdir(cd_arg->curpath);
	if (!test_option("-P"))
		ft_setenv("PWD", cd_arg->new_pwd);
	else
		ft_setenv("PWD", pwd_p());
	//S'il n'y a pas suffisamment d'autorisations sur le nouveau répertoire,
	//ou sur l'un des parents de ce répertoire,
	//pour déterminer le répertoire de travail actuel,
	//la valeur de la variable d'environnement PWD n'est pas spécifiée.
	return (10);
}
