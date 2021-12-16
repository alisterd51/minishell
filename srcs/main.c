/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 04:54:07 by anclarma          #+#    #+#             */
/*   Updated: 2021/12/16 11:31:12 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "builtin.h"
#include "minishell.h"

#include <unistd.h>
#include <signal.h>

static void	intern_exec(char *line, t_list *lst_env)
{
	char	**tab;
	t_ast	*ast;

	tab = line_to_tab(line);
	ast = init_ast(tabsize(tab), tab);
	clean_tab(&tab);
	print_ast(ast, 0);
	ft_set_status(exec_ast(ast, &lst_env));
	clean_ast(&ast);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_list	*lst_env;

	line = readline("\033[1;34mminishell-beta \033[1;32mv0.1\033[0m$ ");
	lst_env = init_env(env);
	while (line)
	{
		add_history(line);
		history_search(line, 1);
		intern_exec(line, lst_env);
		free(line);
		line = NULL;
		if (ft_get_end() == 0)
			line = readline("\033[1;34mminishell-beta \033[1;32mv0.1\033[0m$ ");
	}
	clear_history();
	clean_env(&lst_env);
	(void)ac;
	(void)av;
	return (ft_get_status());
}
