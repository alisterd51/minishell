/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 19:24:23 by anclarma          #+#    #+#             */
/*   Updated: 2022/01/29 00:19:34 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "minishell.h"

static t_arg	*init_arg(char **av)
{
	t_arg	*arg;

	if (*av == NULL || is_redirect(*av) || **av == '|')
		return (NULL);
	arg = (t_arg *)malloc(sizeof(t_arg));
	if (arg == NULL)
	{
		perror("minishell: init_arg");
		return (NULL);
	}
	*arg = (t_arg){.arg = ft_strdup(*av),
		.next = init_arg(av + 1)};
	return (arg);
}

static t_redir	*init_redirect(char **av)
{
	t_redir	*redir;

	while (*av && !is_redirect(*av) && ft_strcmp(*av, "|"))
		av++;
	if (*av == NULL || !is_redirect(*av))
		return (NULL);
	redir = (t_redir *)malloc(sizeof(t_redir));
	if (redir == NULL)
	{
		perror("minishell: init_redirct");
		return (NULL);
	}
	*redir = (t_redir){0};
	if (*av)
		redir->type = is_redirect(*av++);
	if (*av)
		redir->file = ft_strdup(*av++);
	if (*av)
		redir->next = init_redirect(av);
	return (redir);
}

static t_ast	*init_command(char **av)
{
	t_ast	*node;

	node = (t_ast *)malloc(sizeof(t_ast));
	if (node == NULL)
	{
		perror("minishell: init_command");
		return (NULL);
	}
	*node = (t_ast){.type = COMMAND,
		.paw1 = init_arg(av),
		.paw2 = init_redirect(av)};
	return (node);
}

static t_ast	*new_node(t_ast *node_command, int ac, char **av)
{
	t_ast	*node;

	node = (t_ast *)malloc(sizeof(t_ast));
	if (node == NULL)
	{
		clean_ast(&node_command);
		perror("minishell: init_ast");
		return (NULL);
	}
	*node = (t_ast){.type = PIPELINE,
		.paw1 = node_command,
		.paw2 = init_ast(ac - 1, av + 1)};
	return (node);
}

t_ast	*init_ast(int ac, char **av)
{
	t_ast	*node_command;

	node_command = NULL;
	if (ac == 0)
		return (NULL);
	node_command = init_command(av);
	while (*av && **av != '|')
	{
		av++;
		ac--;
	}
	if (*av)
		return (new_node(node_command, ac, av));
	return (node_command);
}
