/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 22:22:58 by lzaccome          #+#    #+#             */
/*   Updated: 2022/02/05 00:19:30 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"

static char	*generate_heredoc(void)
{
	char	new_heredoc[1024];
	char	*add;
	int		add_id;
	int		fd;

	add_id = 0;
	ft_strlcpy(new_heredoc, "/tmp/heredoc", 1024);
	fd = open(new_heredoc, O_WRONLY | O_EXCL | O_CREAT, 0644);
	while (fd == -1 && add_id < INT_MAX)
	{
		ft_strlcpy(new_heredoc, "/tmp/heredoc", 1024);
		add = ft_itoa(add_id);
		if (add == NULL)
			return (NULL);
		ft_strlcat(new_heredoc, add, 1024);
		free(add);
		fd = open(new_heredoc, O_WRONLY | O_EXCL | O_CREAT, 0644);
		add_id++;
	}
	if (fd != -1)
	{
		close(fd);
		return (ft_strdup(new_heredoc));
	}
	return (NULL);
}

static void	free_heredoc_1(void *cpath)
{
	unlink((char *)cpath);
	free(cpath);
}

static char	*intern_herdoc(int mode)
{
	static t_list	*list_heredoc = NULL;
	t_list			*new_node;
	char			*new_name;

	if (mode == 0)
	{
		new_name = generate_heredoc();
		if (new_name == NULL)
			return (NULL);
		new_node = ft_lstnew(new_name);
		if (new_node == NULL)
		{
			free(new_name);
			return (NULL);
		}
		ft_lstadd_front(&list_heredoc, new_node);
		return (new_name);
	}
	else if (mode == 1)
		ft_lstclear(&list_heredoc, free_heredoc_1);
	else if (mode == 2)
		ft_lstclear(&list_heredoc, free);
	return (NULL);
}

void	clean_heredoc(int mode)
{
	if (mode == 1)
		intern_herdoc(1);
	else
		intern_herdoc(2);
}

char	*new_heredoc(void)
{
	return (intern_herdoc(0));
}
