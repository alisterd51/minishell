/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 22:22:58 by lzaccome          #+#    #+#             */
/*   Updated: 2022/02/04 20:39:16 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"

t_arg	*init_arg(t_cmd *lst_token)
{
	t_arg	*arg;

	while (lst_token && lst_token->type != PIPELINE)
	{
		if (is_redirect(lst_token->type))
			lst_token = lst_token->next;
		else
		{
			arg = (t_arg *)malloc(sizeof(t_arg));
			if (arg == NULL)
			{
				perror("minishell: init_arg");
				return (NULL);
			}
			*arg = (t_arg){0};
			arg->arg = ft_strdup(lst_token->word);
			arg->next = init_arg(lst_token->next);
			return (arg);
		}
		lst_token = lst_token->next;
	}
	return (NULL);
}

static t_redir	*sub_init_redirect1(t_redir *redir, t_cmd *lst_token)
{
	redir->type = lst_token->type;
	lst_token = lst_token->next;
	redir->file = ft_strdup(lst_token->word);
	redir->next = init_redirect(lst_token->next);
	return (redir);
}

static t_redir	*sub_init_redirect2(t_redir *redir, t_cmd *lst_token)
{
	int	type_heredoc;

	if (lst_token->type == D_LEFT)
		type_heredoc = 0;
	else
		type_heredoc = 1;
	redir->type = lst_token->type;
	lst_token = lst_token->next;
	redir->file = ft_itoa(fd_heredoc(lst_token->word, type_heredoc));
	redir->next = init_redirect(lst_token->next);
	return (redir);
}

t_redir	*init_redirect(t_cmd *lst_token)
{
	t_redir	*redir;

	while (lst_token && lst_token->type != PIPELINE)
	{
		if (is_redirect(lst_token->type))
		{
			redir = (t_redir *)malloc(sizeof(t_redir));
			if (redir == NULL)
			{
				perror("minishell: init_redirect");
				return (NULL);
			}
			*redir = (t_redir){0};
			if (lst_token->type != D_LEFT && lst_token->type != D_LEFT_EXP)
				return (sub_init_redirect1(redir, lst_token));
			else
				return (sub_init_redirect2(redir, lst_token));
		}
		lst_token = lst_token->next;
	}
	return (NULL);
}

t_ast	*init_command(t_cmd *lst_token)
{
	t_ast	*node;

	node = (t_ast *)malloc(sizeof(t_ast));
	if (node == NULL)
	{
		perror("minishell: init_command");
		return (NULL);
	}
	*node = (t_ast){.type = COMMAND,
		.paw1 = init_arg(lst_token),
		.paw2 = init_redirect(lst_token)};
	return (node);
}