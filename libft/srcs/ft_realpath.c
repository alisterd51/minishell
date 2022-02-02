/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 00:33:06 by anclarma          #+#    #+#             */
/*   Updated: 2022/02/03 00:34:51 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

static void	del_dot(char *path)
{
	char	*new_path;
	size_t	i;
	size_t	j;

	new_path = (char [PATH_MAX]){0};
	i = 0;
	j = 0;
	while (j < PATH_MAX && path[i])
	{
		if (i == 0 && path[i] == '/')
			new_path[j++] = path[i++];
		else if (path[i] == '/')
		{
			new_path[j++] = path[i++];
			while (path[i] == '/')
				i++;
		}
		else if (!ft_strncmp("./", path + i, 2)
			|| !ft_strcmp(".", path + i))
			i++;
		else
			while (path[i] && path[i] != '/')
				new_path[j++] = path[i++];
	}
	ft_strlcpy(path, new_path, PATH_MAX);
}

static void	del_dotdot(char *path)
{
	size_t	j;

	j = 0;
	while (path[j])
	{
		if (!ft_strncmp("../", path + j, 3)
			|| !ft_strcmp("..", path + j))
		{
			path[j] = '/';
			path[j + 1] = '/';
			while (j > 0 && path[j] == '/')
				j--;
			while (j > 0 && path[j] != '/')
				path[j--] = '/';
		}
		else
			j++;
	}
}

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

static void	del_end_slash(char *path)
{
	size_t	i;

	i = 1;
	while (path[i])
		i++;
	i--;
	while (i > 0 && path[i] == '/')
		path[i--] = '\0';
}

char	*ft_realpath(const char *path, char *resolved_path)
{
	char	*new_path;
	char	*pwd;

	if (!path || !resolved_path)
		return (NULL);
	new_path = (char [PATH_MAX]){0};
	pwd = (char [1024]){0};
	if (path[0] != '/')
	{
		getcwd(pwd, 1024);
		ft_strlcpy(new_path, pwd, PATH_MAX);
		ft_strlcat(new_path, "/", PATH_MAX);
	}
	ft_strlcat(new_path, path, PATH_MAX);
	del_dot(new_path);
	del_dotdot(new_path);
	del_double_slash(new_path);
	del_end_slash(new_path);
	ft_strlcpy(resolved_path, new_path, PATH_MAX);
	return (resolved_path);
}
