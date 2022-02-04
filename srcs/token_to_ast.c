/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 22:22:58 by lzaccome          #+#    #+#             */
/*   Updated: 2022/02/04 18:57:02 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"

static t_ast	*new_node(t_ast *node_command, t_cmd *lst_token)
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
		.paw2 = token_to_ast(lst_token->next)};
	return (node);
}

t_ast	*token_to_ast(t_cmd *lst_token)
{
	t_ast	*node_command;

	node_command = NULL;
	if (lst_token == NULL)
		return (NULL);
	node_command = init_command(lst_token);
	while (lst_token && lst_token->type != PIPELINE)
		lst_token = lst_token->next;
	if (lst_token)
		return (new_node(node_command, lst_token));
	return (node_command);
}
