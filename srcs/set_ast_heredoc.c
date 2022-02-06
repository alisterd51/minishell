/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ast_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 19:24:23 by anclarma          #+#    #+#             */
/*   Updated: 2022/02/06 02:08:46 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

static void	set_redirect(t_redir *redir, t_list **lst_env)
{
	char	*file;
	int		type_heredoc;

	if (redir == NULL)
		return ;
	if (redir->type == D_LEFT || redir->type == D_LEFT_EXP)
	{
		if (redir->type == D_LEFT)
			type_heredoc = 0;
		else
			type_heredoc = 1;
		file = redir->file;
		redir->file = ft_itoa(fd_heredoc(file, type_heredoc, lst_env));
		free(file);
	}
}

void	set_ast_heredoc(t_ast *ast, t_list **lst_env)
{
	if (ast == NULL)
		return ;
	if (ast->type == PIPELINE)
	{
		set_ast_heredoc(ast->paw1, lst_env);
		set_ast_heredoc(ast->paw2, lst_env);
	}
	else
	{
		set_redirect(ast->paw2, lst_env);
	}
}
