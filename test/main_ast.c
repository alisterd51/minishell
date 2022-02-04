/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 22:23:41 by anclarma          #+#    #+#             */
/*   Updated: 2022/02/03 22:50:02 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <unistd.h>
#include "minishell.h"
#include "lzac_pars1.h"

int	main(int ac, char **av, char **env)
{
	t_ast	*ast;
	t_list	*lst_env;
	t_cmd	*lst_token;
	int		ret;

	if (ac != 2)
		return (1);
	lst_token = parsing_shell(av[1], env);
	ast = token_to_ast(lst_token);
	free_lst(&lst_token);
	print_ast(ast, 0);
	lst_env = init_env(env);
	exec_ast(ast, &lst_env, &ret);
	clean_env(&lst_env);
	clean_ast(&ast);
	return (ret);
}
