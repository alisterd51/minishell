/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 22:50:52 by antoine           #+#    #+#             */
/*   Updated: 2022/01/13 00:52:36 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	intern_colector(int mode, t_ast **ast)
{
	static t_ast	**save_ast = NULL;

	if (mode == 1)
		save_ast = ast;
	else
		clean_ast(save_ast);
}

void	clean_colector(void)
{
	intern_colector(0, NULL);
}

void	to_clean_colector(t_ast **ast)
{
	intern_colector(1, ast);
}
