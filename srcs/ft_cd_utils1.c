/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 03:52:18 by anclarma          #+#    #+#             */
/*   Updated: 2022/01/03 03:43:27 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** test_home
*/
int	test_home(t_list *env)
{
	while (env)
	{
		if (!ft_strncmp("HOME=", env->content, ft_strlen("HOME=")))
			return (1);
		env = env->next;
	}
	return (0);
}

/*
** test_dot
*/
int	test_dot(char *operand)
{
	if (!ft_strcmp(".", operand))
		return (1);
	return (0);
}

/*
** test_dotdot
*/
int	test_dotdot(char *operand)
{
	if (!ft_strcmp("..", operand))
		return (1);
	return (0);
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
