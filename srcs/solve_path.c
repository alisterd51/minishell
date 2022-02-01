/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:49:00 by anclarma          #+#    #+#             */
/*   Updated: 2022/01/23 01:44:20 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "libft.h"

static void	free_spath(char ***spath)
{
	int	i;

	i = 0;
	if (*spath == NULL)
		return ;
	while ((*spath)[i])
	{
		free((*spath)[i]);
		(*spath)[i] = NULL;
		i++;
	}
	free(*spath);
	*spath = NULL;
}

static size_t	nb_spath(char *path)
{
	size_t	nb;

	nb = 0;
	if (!path)
		return (0);
	if (*path)
		nb++;
	while (*path)
	{
		if (*path == ':')
			nb++;
		path++;
	}
	return (nb);
}

static char	*subpath(char *path, size_t *j)
{
	char	*ret;
	size_t	i;

	ret = NULL;
	i = 0;
	while (path[*j + i] && path[*j + i] != ':')
		i++;
	ret = (char *)malloc(sizeof(char) * (i + 2));
	if (ret == NULL)
		return (NULL);
	ft_strlcpy(ret, path + *j, i + 1);
	ret[i] = '/';
	ret[i + 1] = '\0';
	*j = *j + i + 1;
	return (ret);
}

static char	**split_path(char *path)
{
	char	**spath;
	size_t	nbpath;
	size_t	i;
	size_t	j;

	nbpath = nb_spath(path);
	spath = (char **)malloc(sizeof(char *) * (nbpath + 1));
	i = 0;
	j = 0;
	if (spath == NULL)
		return (NULL);
	while (i < nbpath)
	{
		spath[i] = subpath(path, &j);
		if (spath[i] == NULL)
		{
			free_spath(&spath);
			return (NULL);
		}
		i++;
	}
	spath[i] = NULL;
	return (spath);
}

char	*solve_path(char *path, char *key)
{
	char		**spath;
	char		*tpath;
	struct stat	buf;
	int			i;

	spath = split_path(path);
	tpath = NULL;
	i = 0;
	if (spath == NULL)
		return (NULL);
	while (spath[i])
	{
		tpath = ft_strjoin(spath[i], key);
		if (tpath == NULL || stat(tpath, &buf) == 0)
		{
			free_spath(&spath);
			return (tpath);
		}
		free(tpath);
		i++;
	}
	free_spath(&spath);
	return (ft_strdup(key));
}
