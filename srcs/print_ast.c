/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 19:24:23 by anclarma          #+#    #+#             */
/*   Updated: 2021/09/28 22:04:51 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

static void	print_arg(t_arg *arg, int level)
{
	if (arg == NULL)
		return ;
	printf("%*s%s\n", level, "", arg->arg);
	print_arg(arg->next, level + 1);
}

static void	print_redirect(t_redir *redir, int level)
{
	if (redir == NULL)
		return ;
	printf("%*s%d\n", level, "", redir->type);
	printf("%*s%s\n", level, "", redir->file);
	print_redirect(redir->next, level + 1);
}

void	print_ast(t_ast *ast, int level)
{
	if (ast == NULL)
		return ;
	if (ast->type == PIPELINE)
	{
		print_ast(ast->paw1, level + 1);
		printf("%*s%s\n", level, "", "PIPE");
		print_ast(ast->paw2, level + 1);
	}
	else
	{
		printf("%*s%s\n", level, "", "ARGUMENT");
		print_arg(ast->paw1, level + 1);
		if (ast->paw2)
			printf("%*s%s\n", level, "", "REDIRECT");
		print_redirect(ast->paw2, level + 1);
	}
}
