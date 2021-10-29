/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 04:54:07 by anclarma          #+#    #+#             */
/*   Updated: 2021/10/29 20:22:20 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "builtin.h"
#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*line;
	char	**tab;
	t_ast	*ast;

	line = readline("minishell-beta-v0.1$ ");
	while (line)
	{
		tab = line_to_tab(line);
		ast = init_ast(tabsize(tab), tab);
		clean_tab(&tab);
		print_ast(ast, 0);
		exec_ast(ast, env);
		clean_ast(&ast);
		free(line);
		line = readline("minishell-beta-v0.1$ ");
	}
	(void)ac;
	(void)av;
	(void)env;
	return (0);
}
