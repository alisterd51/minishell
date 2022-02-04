/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 04:54:07 by anclarma          #+#    #+#             */
/*   Updated: 2022/02/04 02:21:36 by anclarma         ###   ########.fr       */
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

static void	intern_exec(char *line, t_list *lst_env)
{
	t_ast	*ast;
	t_cmd	*lst_token;
	char	**env;
	int		status;

	env = list_to_tab(lst_env);
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
	if (ast != NULL)
	{
		status = 0;
		exec_ast(ast, &lst_env, &status);
		ft_set_status(status);
	}
	clean_colector();
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
		if (*line != '\0')
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
