/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 04:54:07 by anclarma          #+#    #+#             */
/*   Updated: 2021/11/24 20:16:29 by anclarma         ###   ########.fr       */
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
	t_list	*lst_env;

	line = readline("minishell-beta-v0.1$ ");
	tab = NULL;
	ast = NULL;
	lst_env = init_env(env);
	while (line)
	{
		tab = line_to_tab(line);
		ast = init_ast(tabsize(tab), tab);
		clean_tab(&tab);
		print_ast(ast, 0);
		exec_ast(ast, &lst_env);
		clean_ast(&ast);
		free(line);
		line = readline("minishell-beta-v0.1$ ");
	}
	clean_env(&lst_env);
	(void)ac;
	(void)av;
	return (0);
}
