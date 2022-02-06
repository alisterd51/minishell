/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 04:54:07 by anclarma          #+#    #+#             */
/*   Updated: 2022/02/06 04:23:53 by anclarma         ###   ########.fr       */
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

#include "lzac_pars1.h"

static int	intern_ast_heredoc(t_ast *ast, t_list **lst_env)
{
	int	prev_status;

	prev_status = ft_get_status();
	ft_set_status(0);
	set_ast_heredoc(ast, lst_env);
	if (ft_get_status() != 0)
		return (1);
	ft_set_status(prev_status);
	return (0);
}

static void	intern_exec(char *line, t_list **lst_env)
{
	t_ast	*ast;
	t_cmd	*lst_token;
	char	**env;
	int		status;

	env = list_to_tab(*lst_env);
	if (env == NULL)
	{
		perror("intern_exec");
		return ;
	}
	lst_token = parsing_shell(line, env);
	clean_tab(&env);
	ast = token_to_ast(lst_token);
	free_lst(&lst_token);
	to_clean_colector(&ast);
	if (!intern_ast_heredoc(ast, lst_env) && ast != NULL)
	{
		status = 0;
		exec_ast(ast, lst_env, &status);
		ft_set_status(status);
	}
	clean_colector();
	clean_heredoc(1);
}

static int	intern_init(char **env, t_list **lst_env)
{
	signal(SIGQUIT, SIG_IGN);
	*lst_env = init_env(env);
	if (*lst_env == NULL)
	{
		perror("minishell: init_env");
		return (1);
	}
	return (0);
}

static void	ft_free(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_list	*lst_env;

	(void)ac;
	(void)av;
	if (intern_init(env, &lst_env))
		return (1);
	signal(SIGINT, handler_int);
	line = readline(DEFAULT_PS1);
	while (line)
	{
		if (*line != '\0')
			add_history(line);
		signal(SIGINT, SIG_IGN);
		intern_exec(line, &lst_env);
		ft_free(&line);
		signal(SIGINT, handler_int);
		if (ft_get_end() == 0)
			line = readline(DEFAULT_PS1);
	}
	if (ft_get_end() == 0)
		ft_putendl_fd("exit", 1);
	clear_history();
	clean_env(&lst_env);
	return (ft_get_status());
}
