/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 19:24:23 by anclarma          #+#    #+#             */
/*   Updated: 2021/09/27 21:51:47 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

static t_red_type	is_redirect(char *str)
{
	if (ft_strcmp(str, "<"))
		return (S_LEFT);
	else if (ft_strcmp(str, "<<"))
		return (D_LEFT);
	else if (ft_strcmp(str, ">"))
		return (S_RIGHT);
	else if (ft_strcmp(str, ">>"))
		return (D_RIGHT);
	else
		return (NONE);
}

static t_arg	*init_arg(char **av)
{
	t_arg	*arg;

	if (*av == NULL || is_redirect(*av))
		return (NULL);
	arg = (t_arg *)malloc(sizeof(t_arg));
	if (arg == NULL)
		return (NULL);
	arg->arg = ft_strdup(*av);
	arg->next = init_arg(av + 1);
	return (arg);
}

static t_redir	*init_redirect(char **av)
{
	t_redir	*redir;

	while (*av == NULL && !is_redirect(*av))
		av++;
	if (*av == NULL)
		return (NULL);
	redir = (t_redir *)malloc(sizeof(t_redir));
	if (redir == NULL)
		return (NULL);
	redir->type = is_redirect(*av);
	av++;
	redir->file = ft_strdup(*av);
	av++;
	redir->next = init_redirect(av);
	return (redir);
}

static t_ast	*init_command(char **av)
{
	t_ast	*node;

	node = (t_ast *)malloc(sizeof(t_ast));
	if (node == NULL)
		return (NULL);
	node->type = COMMAND;
	node->paw1 = init_arg(av);
	node->paw2 = init_redirect(av);
	return (node);
}

t_ast	*init_ast(int ac, char **av)
{
	t_ast	*node;
	t_ast	*node_command;

	node = NULL;
	node_command = NULL;
	if (ac == 0)
		return (NULL);
	node_command = init_command(av);
	while (*av && **av != '|')
	{
		av++;
		ac--;
	}
	if (**av == '|')
	{
		node = (t_ast *)malloc(sizeof(t_ast));
		if (node == NULL)
			return (NULL);
		node->type = PIPELINE;
		node->paw1 = node_command;
		node->paw2 = init_ast(ac - 1, av + 1);
		return (node);
	}
	return (node_command);
}
