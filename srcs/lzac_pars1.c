/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lzac_pars1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 22:22:58 by lzaccome          #+#    #+#             */
/*   Updated: 2022/02/03 03:14:12 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lzac_pars1.h"
#include "minishell.h"

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

int	ft_expstrclen(char *str, char c, int i)
{
	int	j;

	j = 0;
	while (str[i] && str[i] != c && str[i] != '|')
	{
		i++;
		j++;
	}
	return (j);
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

int	lzac_is_redirect(int type)
{
	return (type == REDIRECT_L || type == REDIRECT_R
			|| type == HEREDOC || type == REDIRECT_ADD);
}

static t_arg	*init_arg(t_cmd *lst_token)
{
	t_arg   *arg;

	while (lst_token && lst_token->type != PIPE)
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

	while (lst_token && lst_token->type != PIPE)
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
	while (lst_token && lst_token->type != PIPE)
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
