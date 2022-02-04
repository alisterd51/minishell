/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 22:22:58 by lzaccome          #+#    #+#             */
/*   Updated: 2022/02/04 07:23:03 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include "minishell.h"

static t_arg	*init_arg(t_cmd *lst_token)
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
//il faut une fonction qui vas generer des noms de heredoc et qui vas les clean a la fin
static int	fd_heredoc(char *file, int expend)
{
	int		fd;

	(void)expend;
	fd = open("/tmp/.heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd == -1)
	{
		perror("/tmp/.heredoc");
		return (-1);
	}
	signal(SIGINT, handler_int_heredoc);
	ft_heredoc(fd, file);
	signal(SIGINT, handler_int);
	close(fd);
	fd = open("/tmp/.heredoc", O_RDONLY);
	if (fd == -1)
	{
		perror("/tmp/.heredoc");
		return (-1);
	}
	return (fd);
}

char	*ft_itoa(int n)
{
	char	*nb;
	long	nbtmp;
	int		size;
	int		sign;

	sign = n < 0 ? -1 : 1;
	size = (sign > 0 ? 0 : 1) + (n == 0 ? 1 : 0);
	nbtmp = (long)n * sign;
	while (nbtmp > 0)
	{
		nbtmp /= 10;
		size++;
	}
	if (!(nb = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	nbtmp = (long)n * sign;
	nb[size] = '\0';
	while (--size >= 0)
	{
		nb[size] = nbtmp % 10 + '0';
		nbtmp /= 10;
	}
	if (sign < 0)
		nb[0] = '-';
	return (nb);
}

static t_redir	*init_redirect(t_cmd *lst_token)
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
			{
				redir->type = lst_token->type;
				lst_token = lst_token->next;
				redir->file = ft_strdup(lst_token->word);
				redir->next = init_redirect(lst_token->next);
			}
			else
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
			}
			return (redir);
		}
		lst_token = lst_token->next;
	}
	return (NULL);
}

static t_ast	*init_command(t_cmd *lst_token)
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
