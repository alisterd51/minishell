/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 00:33:06 by anclarma          #+#    #+#             */
/*   Updated: 2022/01/05 21:08:36 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

static void	del_double_slash(char *path)
{
	size_t	i;
	size_t	nbslash;

	i = 0;
	while (path[i])
	{
		nbslash = 0;
		while (path[i + nbslash] == '/')
			nbslash++;
		if (nbslash > 1)
			ft_strlcpy(path + i, path + i + nbslash - 1, PATH_MAX - i);
		i++;
		while (path[i] && path[i] != '/')
			i++;
	}
}
/*
static void	del_end_slash(char *path)
{
	size_t	i;

	i = 1;
	while (path[i])
		i++;
	i--;

}
*/
char	*ft_realpath(const char *path, char *resolved_path)
{
	size_t	i;
	size_t	j;
	char	*new_path;
	char	*tmp_path;
	char	*pwd;

	new_path = (char [PATH_MAX]){0};
	tmp_path = (char [PATH_MAX]){0};
	pwd = (char [1024]){0};
	if (path[0] != '/')
	{
		getcwd(pwd, 1024);
		ft_strlcpy(tmp_path, pwd, PATH_MAX);
		ft_strlcat(tmp_path, "/", PATH_MAX);
	}
	ft_strlcat(tmp_path, path, PATH_MAX);
	i = 0;
	j = 0;
	while (j < PATH_MAX && tmp_path[i])
	{
		if (i == 0 && tmp_path[i] == '/')
			new_path[j++] = tmp_path[i++];
		else if (tmp_path[i] == '/')
		{
			new_path[j++] = tmp_path[i++];
			while (tmp_path[i] == '/')
				i++;
		}
		else if (!ft_strncmp("./", tmp_path + i, 2)
			|| !ft_strcmp(".", tmp_path + i))
			i++;
		else
			while (tmp_path[i] && tmp_path[i] != '/')
				new_path[j++] = tmp_path[i++];
	}
	j = 0;
	while (new_path[j])
	{
		if (!ft_strncmp("../", new_path + j, 3)
			|| !ft_strcmp("..", new_path + j))
		{
			new_path[j] = '/';
			new_path[j + 1] = '/';
			while (j > 0 && new_path[j] == '/')
				j--;
			while (j > 0 && new_path[j] != '/')
			{
				new_path[j] = '/';
				j--;
			}
		}
		else
			j++;
	}
	del_double_slash(new_path);
	j = 1;
	while (new_path[j])
		j++;
	j--;
	while (j > 0 && new_path[j] == '/')
	{
		new_path[j] = '\0';
		j--;
	}
	ft_strlcpy(resolved_path, new_path, PATH_MAX);
	return (resolved_path);
}
