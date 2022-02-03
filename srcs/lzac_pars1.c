/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lzac_pars1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 22:22:58 by lzaccome          #+#    #+#             */
/*   Updated: 2022/02/03 08:17:56 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lzac_pars1.h"
#include "minishell.h"

int	ft_strclen(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (i);
	else
		return (-1);
}

int	ft_expstrclen(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c && str[i] != '|')
		i++;
	return (i);
}

int	ft_strarglen(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '<' && str[i] != '>' && str[i] != '|'
		&& str[i] != ' ' && str[i] != '\'' && str[i] != '\"')
		i++;
	return (i);
}

t_cmd	*parsing_shell(char *str, char **envp)
{
	t_cmd	*cmd;

	cmd = get_cmd(str, envp);
	return (cmd);
}

int	lzac_is_redirect(int type)
{
	return (type == S_LEFT || type == S_RIGHT || type == D_LEFT
		|| type == D_RIGHT || type == D_LEFT_EXP);
}

static t_arg	*init_arg(t_cmd *lst_token)
{
	t_arg	*arg;

	while (lst_token && lst_token->type != PIPELINE)
	{
		if (lzac_is_redirect(lst_token->type))
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

static t_redir	*init_redirect(t_cmd *lst_token)
{
	t_redir	*redir;

	while (lst_token && lst_token->type != PIPELINE)
	{
		if (lzac_is_redirect(lst_token->type))
		{
			redir = (t_redir *)malloc(sizeof(t_redir));
			if (redir == NULL)
			{
				perror("minishell: init_redirect");
				return (NULL);
			}
			*redir = (t_redir){0};
			redir->type = lst_token->type;
			lst_token = lst_token->next;
			redir->file = ft_strdup(lst_token->word);
			redir->next = init_redirect(lst_token->next);
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

void	print_token(t_cmd *lst_token)
{
	while (lst_token)
	{
		printf("token : %s, %d, %d\n", lst_token->word, lst_token->type,
			lst_token->space);
		lst_token = lst_token->next;
	}
}
