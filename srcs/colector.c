/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 22:50:52 by antoine           #+#    #+#             */
/*   Updated: 2022/02/06 03:59:20 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	intern_colector(int mode, void *data)
{
	static t_ast	**save_ast = NULL;
	static t_list	*list_fd = NULL;

	if (mode == 0)
	{
		clean_ast(save_ast);
		ft_lstclear(&list_fd, close_fd);
	}
	else if (mode == 1)
		save_ast = (t_ast **)data;
	else if (mode == 2)
		ft_lstadd_back(&list_fd, ft_lstnew(new_int(*(int *)data)));
}

void	clean_colector(void)
{
	intern_colector(0, NULL);
}

void	to_clean_colector(t_ast **ast)
{
	intern_colector(1, ast);
}

void	to_fd_colector(int fd)
{
	intern_colector(2, &fd);
}
