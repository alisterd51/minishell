/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 03:52:18 by anclarma          #+#    #+#             */
/*   Updated: 2022/01/24 17:08:52 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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
	static char	*subpath = NULL;
	char		*subcdpath;
	size_t		i;

	if (subpath == NULL)
		subpath = cdpath;
	if (subpath[0] == '\0')
	{
		subpath = NULL;
		return (NULL);
	}
	i = 0;
	while (subpath[i] && subpath[i] != ':')
		i++;
	if (i == 0)
		subcdpath = ft_strdup(".");
	else
		subcdpath = ft_strndup(subpath, i);
	if (subcdpath == NULL)
		return (NULL);
	subpath += i;
	if (subpath[0] == ':')
		subpath++;
	return (subcdpath);
}

/*
** ft_concatenation
*/
char	*ft_concatenation(char *str1, char *str2, char *str3)
{
	char	*str;
	int		i;
	int		j;

	str = (char *)malloc(sizeof(char)
			* (ft_strlen(str1) + ft_strlen(str2) + ft_strlen(str3) + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (str1[j])
		str[i++] = str1[j++];
	j = 0;
	while (str2[j])
		str[i++] = str2[j++];
	j = 0;
	while (str3[j])
		str[i++] = str3[j++];
	str[i] = '\0';
	return (str);
}
