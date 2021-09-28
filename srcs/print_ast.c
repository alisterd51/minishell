/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 19:24:23 by anclarma          #+#    #+#             */
/*   Updated: 2021/09/28 17:28:12 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

static void	print_arg(t_arg *arg)
{
	if (arg == NULL)
		return ;
	printf("%s\n", arg->arg);
	print_arg(arg->next);
}

static void	print_redirect(t_redir *redir)
{
	if (redir == NULL)
		return ;
	printf("%d, %s\n", redir->type, redir->file);
	print_redirect(redir->next);
}

void	print_ast(t_ast *ast)
{
	if (ast == NULL)
		return ;
	if (ast->type == PIPELINE)
	{
		print_ast(ast->paw1);
		printf("PIPE\n");
		print_ast(ast->paw2);
	}
	else
	{
		printf("ARGUMENT\n");
		print_arg(ast->paw1);
		if (ast->paw2)
			printf("REDIRECT\n");
		print_redirect(ast->paw2);
	}
}
