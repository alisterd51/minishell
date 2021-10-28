/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 22:23:41 by anclarma          #+#    #+#             */
/*   Updated: 2021/10/28 22:24:11 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <unistd.h>
#include "minishell.h"

#define OUTPUT_END	0
#define INPUT_END	1

int	main(int ac, char **av, char **env)
{
	t_ast	*ast;
	int		ret;

	ast = init_ast(ac - 1, av + 1);
	print_ast(ast, 0);
	ret = exec_ast(ast, env);
	clean_ast(&ast);
	return (ret);
}
