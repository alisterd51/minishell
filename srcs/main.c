/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 04:54:07 by anclarma          #+#    #+#             */
/*   Updated: 2021/11/29 18:15:25 by antoine          ###   ########.fr       */
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

void	parse_quotes(char *line)
{
	size_t	single_quotes;
	size_t	double_quotes;
	size_t	i;

	single_quotes = 0;
	double_quotes = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			single_quotes++;
		}
		else if (line[i] == '\"')
		{
			double_quotes++;
		}
		write(1, line + i, 1);
		if ((single_quotes > 0 || double_quotes > 0)
			&& (single_quotes % 2 == 0 && double_quotes % 2 == 0))
			write(1, "\n", 1);
		i++;
	}
}

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
		add_history(line);
		history_search(line, 1);
		tab = line_to_tab(line);
//		parse_quotes(line);
		ast = init_ast(tabsize(tab), tab);
		clean_tab(&tab);
		print_ast(ast, 0);
		exec_ast(ast, &lst_env);
		clean_ast(&ast);
		free(line);
		line = readline("minishell-beta-v0.1$ ");
	}
	clear_history();
	clean_env(&lst_env);
	(void)ac;
	(void)av;
	return (0);
}
