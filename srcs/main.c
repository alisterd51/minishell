/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 04:54:07 by anclarma          #+#    #+#             */
/*   Updated: 2021/10/28 23:52:35 by anclarma         ###   ########.fr       */
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

	line = readline("minishell-beta-v0.1$ ");
	while (line)
	{
		free(line);
		line = readline("minishell-beta-v0.1$ ");
	}
	(void)ac;
	(void)av;
	(void)env;
	return (0);
}
