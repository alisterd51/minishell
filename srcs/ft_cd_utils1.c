/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 03:52:18 by anclarma          #+#    #+#             */
/*   Updated: 2021/12/23 17:07:08 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** test_home
*/
int	test_home(t_list **env)
{
	(void)env;
	return (1);
}

/*
** test_dot
*/
int	test_dot(char *operand)
{
	(void)operand;
	return (1);
}

/*
** test_dotdot
*/
int	test_dotdot(char *operand)
{
	(void)operand;
	return (1);
}

/*
** get_subcdpath
*/
char	*get_subcdpath(char *cdpath)
{
	(void)cdpath;
	return (cdpath);
}

/*
** ft_concatenation
*/
char	*ft_concatenation(char *str1, char *str2, char *str3)
{
	(void)str1;
	(void)str2;
	(void)str3;
	return (str1);
}

/*
** test_directory
*/
int	test_directory(char *path_dir)
{
	(void)path_dir;
	return (1);
}

/*
** test_option
*/
int	test_option(char *option)
{
	(void)option;
	return (1);
}

/*
** clean_a
*/
char	*clean_a(char *curpath)
{
	(void)curpath;
	return (curpath);
}

/*
** clean_b
*/
char	*clean_b(char *curpath)
{
	(void)curpath;
	return (curpath);
}

/*
** clean_c
*/
char	*clean_c(char *curpath)
{
	(void)curpath;
	return (curpath);
}

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
