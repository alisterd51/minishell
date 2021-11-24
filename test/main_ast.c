/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 22:23:41 by anclarma          #+#    #+#             */
/*   Updated: 2021/11/24 21:11:48 by anclarma         ###   ########.fr       */
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
	t_list	*lst_env;
	int		ret;

	ast = init_ast(ac - 1, av + 1);
	print_ast(ast, 0);
	lst_env = init_env(env);
	ret = exec_ast(ast, &lst_env);
	clean_env(&lst_env);
	clean_ast(&ast);
	return (ret);
}
