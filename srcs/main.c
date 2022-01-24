/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 04:54:07 by anclarma          #+#    #+#             */
/*   Updated: 2022/01/24 23:39:23 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "builtin.h"
#include "minishell.h"
#define PROMPT	"\033[1;34mminishell-beta \033[1;32mv0.1\033[0m$ "

static void	intern_exec(char *line, t_list *lst_env)
{
	char	**tab;
	t_ast	*ast;
	int		status;

	tab = line_to_tab(line);
	ast = init_ast(tabsize(tab), tab);
	if (ast == NULL)
		perror("minishell: init_ast");
	to_clean_colector(&ast);
	clean_tab(&tab);
	print_ast(ast, 0);
	(void)lst_env;
	exec_ast(ast, &lst_env, &status);
	ft_set_status(status);
	clean_ast(&ast);
}

static int	intern_init(char **env)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	lst_env = init_env(env);
	if (lst_env == NULL)
	{
		perror("minishell: init_env");
		return (1);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_list	*lst_env;

	(void)ac;
	(void)av;
	if (intern_init(env))
		return (1);
	line = readline(PROMPT);
	while (line)
	{
		add_history(line);
		history_search(line, 1);
		intern_exec(line, lst_env);
		free(line);
		line = NULL;
		if (ft_get_end() == 0)
			line = readline(PROMPT);
	}
	if (ft_get_end() == 0)
		ft_putendl_fd("exit", 1);
	clear_history();
	clean_env(&lst_env);
	return (ft_get_status());
}
