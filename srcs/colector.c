/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 22:50:52 by antoine           #+#    #+#             */
/*   Updated: 2022/02/04 22:03:35 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"

static void	close_fd(void *ptr)
{
	int	*fd;

	fd = (int *)ptr;
	close(*fd);
	free(fd);
}

static int	*new_int(int i)
{
	int	*ret;

	ret = (int *)malloc(sizeof(int) * 1);
	if (ret == NULL)
		return (NULL);
	ret[0] = i;
	return (ret);
}

static void	intern_colector(int mode, t_ast **ast, int fd)
{
	static t_ast	**save_ast = NULL;
	static t_list	*list_fd = NULL;

	if (mode == 0)
	{
		clean_ast(save_ast);
		ft_lstclear(&list_fd, close_fd);
	}
	else if (mode == 1)
		save_ast = ast;
	else if (mode == 2)
		ft_lstadd_back(&list_fd, ft_lstnew(new_int(fd)));
}

void	clean_colector(void)
{
	intern_colector(0, NULL, 0);
}

void	to_clean_colector(t_ast **ast)
{
	intern_colector(1, ast, 0);
}

void	to_fd_colector(int fd)
{
	intern_colector(2, NULL, fd);
}
