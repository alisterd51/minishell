/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 22:22:58 by lzaccome          #+#    #+#             */
/*   Updated: 2022/02/04 18:25:49 by anclarma         ###   ########.fr       */
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

static void	free_heredoc(void *cpath)
{
	unlink((char *)cpath);
	free(cpath);
}

static char	*intern_herdoc(int mode)
{
	static t_list	*list_heredoc = NULL;
	char			*new_name;

	if (mode == 0)
	{
		new_name = generate_heredoc();
		ft_lstadd_front(&list_heredoc, ft_lstnew(new_name));
		return (new_name);
	}
	else if (mode == 1)
		ft_lstclear(&list_heredoc, free_heredoc);
	return (NULL);
}

void	clean_heredoc(void)
{
	intern_herdoc(1);
}

char	*new_heredoc(void)
{
	return (intern_herdoc(0));
}
