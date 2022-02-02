/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lzac_pars1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 22:22:58 by lzaccome          #+#    #+#             */
/*   Updated: 2022/02/02 06:06:55 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lzac_pars1.h"

int	ft_strclen(char *str, char c, int i)
{
	int	j;

	j = 0;
	while (str[i] && str[i] != c)
	{
		i++;
		j++;
	}
	if (str[i] == c)
		return (j);
	else
		return (-1);
}

int	ft_strarglen(char *str, int i)
{
	int	j;

	j = 0;
	while (str[i] && str[i] != '<' && str[i] != '>' && str[i] != '|'
		&& str[i] != ' ' && str[i] != '\'' && str[i] != '\"')
	{
		i++;
		j++;
	}
	return (j);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = 0;
		i++;
	}
}

char	*lzac_ft_strndup(char *str, int size, int i)
{
	char	*word;
	int		j;

	j = 0;
	word = malloc(sizeof(char) * size + 1);
	if (!word)
		return (NULL);
	while (str[i] && j < size)
	{
		word[j] = str[i];
		i++;
		j++;
	}
	word[j] = '\0';
	return (word);
}

t_cmd	*parsing_shell(char *str, char **envp)
{
	t_cmd	*cmd;

	(void)envp;
	cmd = get_cmd(str, envp);
	return (cmd);
}
/*
//
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
//en cours de construction
t_ast	*token_to_ast(t_cmd *lst_token)
{
	t_ast	*node_command;

	node_command = NULL;
	if (lst_token == NULL)
		return (NULL);
	node_command = init_command(lst_token);
	while (lst_token->type != PIPE)
		lst_token = lst_token->next;
	if (lst_token)
		return (new_node(node_command, lst_token));
	return (node_command);
}
*/
t_ast	*token_to_ast(t_cmd *lst_token)
{
	(void)lst_token;
	return (NULL);
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

char	*lzac_ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*dst;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1) + ft_strlen(s2);
	dst = (char *)malloc(sizeof(char) * (i + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		dst[i + j] = s2[j];
		j++;
	}
	dst[i + j] = '\0';
	free(s1);
	return (dst);
}
