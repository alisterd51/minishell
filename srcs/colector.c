/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 22:50:52 by antoine           #+#    #+#             */
/*   Updated: 2022/02/06 05:23:45 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

static int	intern_colector(int mode, void *data)
{
	static t_ast	**save_ast = NULL;
	static t_list	*list_fd = NULL;
	int				*new_int_ptr;
	t_list			*new_node;

	if (mode == 0)
	{
		clean_ast(save_ast);
		ft_lstclear(&list_fd, close_fd);
	}
	else if (mode == 1)
		save_ast = (t_ast **)data;
	else if (mode == 2)
	{
		new_int_ptr = new_int(*(int *)data);
		new_node = ft_lstnew(new_int_ptr);
		if (!new_int_ptr || !new_node)
		{
			free(new_int_ptr);
			ft_lstdelone(new_node, free);
			return (-1);
		}
		ft_lstadd_back(&list_fd, new_node);
	}
	return (0);
}

void	clean_colector(void)
{
	intern_colector(0, NULL);
}

void	to_clean_colector(t_ast **ast)
{
	intern_colector(1, ast);
}

int	to_fd_colector(int fd)
{
	return (intern_colector(2, &fd));
}
