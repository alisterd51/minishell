/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 03:52:18 by anclarma          #+#    #+#             */
/*   Updated: 2021/12/22 17:29:23 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <linux/limits.h>
#include <unistd.h>
#include "libft.h"

/*
** t_cd
*/
typedef struct s_cd	t_cd;
struct	s_cd
{
	char	*curpath;
	char	*operand;
	char	*new_pwd;
	t_list	**env;
	int		ret;
};

/*
** test_home
*/
static int	test_home(t_list **env)
{
	(void)env;
	return (1);
}

/*
** test_dot
*/
static int	test_dot(char *operand)
{
	(void)operand;
	return (1);
}

/*
** test_dotdot
*/
static int	test_dotdot(char *operand)
{
	(void)operand;
	return (1);
}

/*
** get_subcdpath
*/
static char	*get_subcdpath(char *cdpath)
{
	(void)cdpath;
	return (cdpath);
}

/*
** ft_concatenation
*/
static char	*ft_concatenation(char *str1, char *str2, char *str3)
{
	(void)str1;
	(void)str2;
	(void)str3;
	return (str1);
}

/*
** test_directory
*/
static int	test_directory(char *path_dir)
{
	(void)path_dir;
	return (1);
}

/*
** test_option
*/
static int	test_option(char *option)
{
	(void)option;
	return (1);
}

/*
** clean_a
*/
static char	*clean_a(char *curpath)
{
	(void)curpath;
	return (curpath);
}

/*
** clean_b
*/
static char	*clean_b(char *curpath)
{
	(void)curpath;
	return (curpath);
}

/*
** clean_c
*/
static char	*clean_c(char *curpath)
{
	(void)curpath;
	return (curpath);
}

/*
** to_relative
*/
static char	*to_relative(char *curpath, char *operand)
{
	(void)curpath;
	(void)operand;
	return (curpath);
}

/*
** ft_getenv
*/
static char	*ft_getenv(char *key)
{
	(void)key;
	return (ft_strdup(""));
}

/*
** ft_setenv
*/
static void	ft_setenv(char *key, char *value)
{
	(void)key;
	(void)value;
}

int	step0(t_cd *cd_arg)
{
	if (cd_arg->operand == NULL && !test_home(cd_arg->env))
		return (10);
	return (1);
}

int	step1(t_cd *cd_arg)
{
	if (cd_arg->operand == NULL && test_home(cd_arg->env))
		cd_arg->operand = ft_getenv("HOME");
	return (2);
}

int	step2(t_cd *cd_arg)
{
	if (cd_arg->operand[0] == '/')
	{
		cd_arg->curpath = cd_arg->operand;
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

	cdpath = ft_getenv("CDPATH");
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
			cd_arg->curpath = ft_concatenation(pwd , "", cd_arg->curpath);
		else
			cd_arg->curpath = ft_concatenation(pwd , "/", cd_arg->curpath);
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

int	step8(t_cd *cd_arg)
{
	cd_arg->new_pwd = cd_arg->curpath;
	if (ft_strlen(cd_arg->curpath) + 1 > PATH_MAX
			&& ft_strlen(cd_arg->operand) + 1 < PATH_MAX)
		cd_arg->curpath = to_relative(cd_arg->curpath, cd_arg->operand);
	//incompler mais bon a priori
	return (9);
}

int	step9(t_cd *cd_arg)
{
	cd_arg->ret = chdir(cd_arg->curpath);
	//si erreur affichage message d'erreur et fin
	if (!test_option("-P"))
		ft_setenv("PWD", cd_arg->new_pwd);
	else
	{
		//la variable d'environnement PWD doit être définie sur la chaîne qui serait sortie par pwd -P.
	}
	//S'il n'y a pas suffisamment d'autorisations sur le nouveau répertoire, ou sur l'un des parents de ce répertoire, pour déterminer le répertoire de travail actuel, la valeur de la variable d'environnement PWD n'est pas spécifiée.
	return (10);
}

/*
** ft_cd
** https://pubs.opengroup.org/onlinepubs/9699919799/utilities/cd.html
*/
int	ft_cd(int ac, char **av, t_list **env)
{
	int		step;
	t_cd	cd_var;
	int		(*fonc_step[10]) (t_cd *) = {step0, step1, step2, step3, step4,
		step5, step6, step7, step8, step9};

	cd_var = (t_cd){.env = env};
	if (ac >= 2)
		cd_var.operand = ft_strdup(av[1]);
	{
		step = 0;
		while (step < 10)
			step = (fonc_step[step])(&cd_var);
	}
	//Si, pendant l'exécution des étapes ci-dessus, la variable d'environnement PWD est définie, la variable d'environnement OLDPWD doit également être définie sur la valeur de l'ancien répertoire de travail (c'est-à-dire le répertoire de travail actuel immédiatement avant l'appel à cd ).
	return (cd_var.ret);
}
