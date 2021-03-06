/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 04:54:07 by anclarma          #+#    #+#             */
/*   Updated: 2022/01/29 16:35:51 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include "builtin.h"
#include "minishell.h"

static void	intern_exec(char *line, t_list *lst_env)
{
	char	**tab;
	t_ast	*ast;
	int		status;

	tab = line_to_tab(line);
	ast = init_ast(tabsize(tab), tab);
	to_clean_colector(&ast);
	clean_tab(&tab);
	print_ast(ast, 0);
	(void)lst_env;
	exec_ast(ast, &lst_env, &status);
	ft_set_status(status);
	clean_ast(&ast);
}

static int	intern_init(char **env, t_list **lst_env)
{
	signal(SIGINT, handler_int);
	signal(SIGQUIT, SIG_IGN);
	*lst_env = init_env(env);
	if (*lst_env == NULL)
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
	if (intern_init(env, &lst_env))
		return (1);
	line = readline(DEFAULT_PS1);
	while (line)
	{
		add_history(line);
		intern_exec(line, lst_env);
		free(line);
		line = NULL;
		if (ft_get_end() == 0)
			line = readline(DEFAULT_PS1);
	}
	if (ft_get_end() == 0)
		ft_putendl_fd("exit", 1);
	clear_history();
	clean_env(&lst_env);
	return (ft_get_status());
}
