/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 18:38:25 by anclarma          #+#    #+#             */
/*   Updated: 2021/09/28 19:17:48 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

static void	clean_arg(t_arg **arg)
{
	if (*arg == NULL)
		return ;
	free((*arg)->arg);
	clean_arg(&((*arg)->next));
	free(*arg);
	*arg = NULL;
}

static void	clean_redirect(t_redir **redir)
{
	if (*redir == NULL)
		return ;
	free((*redir)->file);
	(*redir)->file = NULL;
	clean_redirect(&((*redir)->next));
	free(*redir);
	*redir = NULL;
}

void	clean_ast(t_ast **ast)
{
	if (*ast == NULL)
		return ;
	if ((*ast)->type == PIPELINE)
	{
		clean_ast((t_ast **)&((*ast)->paw1));
		clean_ast((t_ast **)&((*ast)->paw2));
	}
	else
	{
		clean_arg((t_arg **)&((*ast)->paw1));
		clean_redirect((t_redir **)&((*ast)->paw2));
	}
	free(*ast);
	*ast = NULL;
}
