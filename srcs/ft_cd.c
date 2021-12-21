/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 03:52:18 by anclarma          #+#    #+#             */
/*   Updated: 2021/12/21 23:32:18 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <linux/limits.h>
#include <unistd.h>
#include "libft.h"

/*
** test_home
*/
static int	test_home(t_list *env)
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

/*
** ft_cd
** https://pubs.opengroup.org/onlinepubs/9699919799/utilities/cd.html
*/
int	ft_cd(int ac, char **av, t_list **env)
{
	char	*curpath;
	char	*operand;
	char	*new_pwd;
	int		ret;
	int		step;

	curpath = NULL;
	ret = 0;
	step = 1;
	if (ac >= 2)
		operand = ft_strdup(av[1]);
	if (step == 1)
	{
		step = 2;
		if (ac == 1 && !test_home(*env))
			step = 11;
	}
	if (step == 2)
	{
		step = 3;
		if (ac == 1 && test_home(*env))
			operand = ft_getenv("HOME");
	}
	if (step == 3)
	{
		step = 4;
		if (operand[0] == '/')
		{
			curpath = operand;
			step = 7;
		}
	}
	if (step == 4)
	{
		step = 5;
		if (test_dot(operand) || test_dotdot(operand))
			step = 6;
	}
	if (step == 5)
	{
		step = 6;
		char	*subcdpath;
		char	*cdpath;

		cdpath = ft_getenv("CDPATH");
		if (cdpath == NULL)
			cdpath = "";
		subcdpath = get_subcdpath(cdpath);
		while (step == 6 && subcdpath != NULL)
		{
			char	*concatenation;

			concatenation = ft_concatenation(subcdpath, "/", operand);
			if (test_directory(concatenation))
			{
				curpath = concatenation;
				step = 7;
			}
			subcdpath = get_subcdpath(cdpath);
		}
	}
	if (step == 6)
	{
		step = 7;
		curpath = operand;
	}
	if (step == 7)
	{
		step = 8;
		if (test_option("-P"))
			step = 10;
		else
		{
			if (curpath[0] != '/')
			{
				char	*pwd;

				pwd = ft_getenv("PWD");
				if (pwd[ft_strlen(pwd) - 1] == '/')
					curpath = ft_concatenation(pwd , "", curpath);
				else
					curpath = ft_concatenation(pwd , "/", curpath);
			}
		}
	}
	if (step == 8)
	{
		step = 9;
		curpath = clean_a(curpath);
		curpath = clean_b(curpath);
		curpath = clean_c(curpath);
	}
	if (step == 9)
	{
		new_pwd = curpath;
		step = 10;
		if (ft_strlen(curpath) + 1 > PATH_MAX && ft_strlen(operand) + 1 < PATH_MAX)
			curpath = to_relative(curpath, operand);
		//incompler mais bon a priori
	}
	if (step == 10)
	{
		step = 11;
		ret = chdir(curpath);
		//si erreur affichage message d'erreur et fin
		if (!test_option("-P"))
			ft_setenv("PWD", new_pwd);
		else
		{
			//la variable d'environnement PWD doit être définie sur la chaîne qui serait sortie par pwd -P.
		}
		//S'il n'y a pas suffisamment d'autorisations sur le nouveau répertoire, ou sur l'un des parents de ce répertoire, pour déterminer le répertoire de travail actuel, la valeur de la variable d'environnement PWD n'est pas spécifiée.
	}
	//Si, pendant l'exécution des étapes ci-dessus, la variable d'environnement PWD est définie, la variable d'environnement OLDPWD doit également être définie sur la valeur de l'ancien répertoire de travail (c'est-à-dire le répertoire de travail actuel immédiatement avant l'appel à cd ).
	return (ret);
}
