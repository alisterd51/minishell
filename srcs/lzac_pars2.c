/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lzac_pars2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 17:50:28 by lzaccome          #+#    #+#             */
/*   Updated: 2022/02/03 03:05:41 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lzac_pars1.h"
#include "minishell.h"

void	free_lst(t_cmd **cmd)
{
	t_cmd	*tmp;

	tmp = *cmd;
	while (tmp)
	{
		*cmd = tmp;
		tmp = tmp->next;
		if ((*cmd)->type != REDIRECT_L && (*cmd)->type != REDIRECT_R
			&& (*cmd)->type != REDIRECT_ADD && (*cmd)->type != HEREDOC
			&& (*cmd)->type != PIPE && (*cmd)->type != DOLLAR)
			free((*cmd)->word);
		free(*cmd);
	}
}

t_cmd	*lzac_ft_lstnew(char *word, enum e_type type, int space)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->word = word;
	cmd->type = type;
	cmd->space = space;
	cmd->next = NULL;
	return (cmd);
}

void	lzac_ft_lstadd_back(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*begin;

	begin = (*cmd);
	if (begin == NULL)
		(*cmd) = new;
	else
	{
		while (begin->next)
			begin = begin->next;
		begin->next = new;
	}
}

int	lzac_ft_lstsize(t_cmd *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	ft_space(t_stuff *stuff, char *str)
{
	while (ft_isspace(str[stuff->i]))
		stuff->i++;
	stuff->space = 1;
}

int	ft_quote(t_stuff *stuff, char c, t_cmd **cmd)
{
	t_cmd	*new;
	char	*word;
	int		j;

	j = 0;
	if (stuff->str[stuff->i + 1])
		stuff->i++;
	else
	{
		print_error("unclosed quote\n", *cmd);
		return (1);
	}
	j = ft_strclen(stuff->str, c, stuff->i);
	if (j < 0)
	{
		print_error("unclosed quote\n", *cmd);
		return (1);
	}
	word = lzac_ft_strndup(stuff->str, j, stuff->i);
	new = lzac_ft_lstnew(word, ARG, stuff->space);
	lzac_ft_lstadd_back(cmd, new);
	stuff->i += j + 1;
	return (0);
}

void	ft_alnum(t_stuff *stuff, t_cmd **cmd)
{
	int		j;
	char	*word;
	t_cmd	*new;

	j = 0;
	stuff->type = ARG;
	j = ft_strarglen(stuff->str, stuff->i);
	word = lzac_ft_strndup(stuff->str, j, stuff->i);
	new = lzac_ft_lstnew(word, stuff->type, stuff->space);
	lzac_ft_lstadd_back(cmd, new);
	stuff->i += j;
}

void	ft_rdleft(t_stuff *stuff, t_cmd **cmd)
{
	t_cmd	*new;

	stuff->i++;
	stuff->type = REDIRECT_L;
	if (stuff->str[stuff->i] && stuff->str[stuff->i] == '<')
	{
		stuff->type = HEREDOC;
		new = lzac_ft_lstnew("<<", stuff->type, stuff->space);
		stuff->i++;
	}
	else
		new = lzac_ft_lstnew("<", stuff->type, stuff->space);
	lzac_ft_lstadd_back(cmd, new);
}

void	ft_rdright(t_stuff *stuff, t_cmd **cmd)
{
	t_cmd	*new;

	stuff->i++;
	stuff->type = REDIRECT_R;
	if (stuff->str[stuff->i] && stuff->str[stuff->i] == '>')
	{
		stuff->type = REDIRECT_ADD;
		new = lzac_ft_lstnew(">>", stuff->type, stuff->space);
		stuff->i++;
	}
	else
		new = lzac_ft_lstnew(">", stuff->type, stuff->space);
	lzac_ft_lstadd_back(cmd, new);
}

void	lzac_ft_pipe(t_stuff *stuff, t_cmd **cmd)
{
	t_cmd	*new;

	stuff->type = PIPE;
	new = lzac_ft_lstnew("|", stuff->type, stuff->space);
	lzac_ft_lstadd_back(cmd, new);
	stuff->i++;
}

void	init_stuff(t_stuff *stuff, char *str)
{
	stuff->str = str;
	stuff->i = 0;
	stuff->space = 0;
	stuff->type = LZAC_NONE;
}

void	ft_expend(t_stuff *stuff, char **envp, t_cmd **cmd)
{
	t_cmd	*new;
	char	*word;
	int		j;

	(void)envp;
	j = 0;
	stuff->i++;
	stuff->type = EXPEND;
	j = ft_expstrclen(stuff->str, ' ', stuff->i);
	if (j == 0)
	{
		word = "$";
		stuff->type = DOLLAR;
	}
	else
		word = lzac_ft_strndup(stuff->str, j, stuff->i);
	new = lzac_ft_lstnew(word, stuff->type, stuff->space);
	lzac_ft_lstadd_back(cmd, new);
	// if (j == 0)
	// 	stuff->i++;
	// else
		stuff->i += j;
}

t_cmd	*get_cmd(char *str, char **envp)
{
	t_cmd		*cmd;
	t_stuff		stuff;

	(void)envp;
	cmd = NULL;
	init_stuff(&stuff, str);
	while (str[stuff.i])
	{
		stuff.type = LZAC_NONE;
		stuff.space = 0;
		if (ft_isspace(str[stuff.i]))
			ft_space(&stuff, str);
		if (str[stuff.i] == '\'')
		{
			if (ft_quote(&stuff, '\'', &cmd) == 1)
				return (NULL);
		}
		else if (str[stuff.i] == '\"')
		{
			if (ft_quote(&stuff, '\"', &cmd) == 1)
				return (NULL);
		}
		else if (str[stuff.i] == '<')
			ft_rdleft(&stuff, &cmd);
		else if (str[stuff.i] == '>')
			ft_rdright(&stuff, &cmd);
		else if (ft_isalnum(str[stuff.i]) || str[stuff.i] == '/'
			|| str[stuff.i] == '-' || str[stuff.i] == '.')
			ft_alnum(&stuff, &cmd);
		else if (str[stuff.i] == '|')
			lzac_ft_pipe(&stuff, &cmd);
		else if (str[stuff.i] == '$')
			ft_expend(&stuff, envp, &cmd);
		else
		{
			if (stuff.space != 1)
				stuff.i++;
		}
	}
	get_type(cmd);
	if (get_error(cmd) == 2)
		return (NULL);
	return (cmd);
}

void	get_type(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_cmd	*tmp2;

	tmp = cmd;
	while (tmp)
	{
		if (tmp && tmp->next && (tmp->type == REDIRECT_L
				|| tmp->type == REDIRECT_R || tmp->type == REDIRECT_ADD))
		{
			if (tmp->next->type == REDIRECT_L || tmp->next->type == REDIRECT_R
				|| tmp->next->type == REDIRECT_ADD
				|| tmp->next->type == HEREDOC)
				print_error("syntax error near unexpected token redirection\n", cmd);
			else if (tmp->next->type == PIPE)
				print_error("syntax error near unexpected token `|'\n", cmd);
			tmp->next->type = T_FILE;
		}
		if (tmp && tmp->next && tmp->type == HEREDOC)
		{
			if (tmp->next->type == REDIRECT_L || tmp->next->type == REDIRECT_R
				|| tmp->next->type == REDIRECT_ADD
				|| tmp->next->type == HEREDOC)
				print_error("syntax error near unexpected token redirection\n", cmd);
			else if (tmp->next->type == PIPE)
				print_error("syntax error near unexpected token `|'\n", cmd);
			tmp->next->type = DELIMITOR;
		}
		if (tmp->next && tmp->next->space == 0 && tmp->type == 1
			&& tmp->next->type == 1)
		{
			tmp->word = lzac_ft_strjoin(tmp->word, tmp->next->word);
			tmp2 = tmp->next;
			tmp->next = tmp->next->next;
			free(tmp2->word);
			free(tmp2);
		}
		else
			tmp = tmp->next;
	}
}

int	get_error(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		size;
	int		i;

	tmp = cmd;
	size = lzac_ft_lstsize(cmd);
	i = 1;
	while (cmd)
	{
		if (cmd && cmd->next && cmd->type == PIPE && cmd->next->type == PIPE)
		{
			print_error("syntax error near unexpected token `|'\n", tmp);
			return (2);
		}
		if (i == 1 && cmd->type == PIPE)
		{
			print_error("syntax error near unexpected token `|'\n", tmp);
			return (2);
		}
		if (i == size && (cmd->type == REDIRECT_L || cmd->type == REDIRECT_R
				|| cmd->type == REDIRECT_ADD || cmd->type == HEREDOC || cmd->type == PIPE))
		{
			print_error("syntax error near unexpected token `newline'\n", tmp);
			return (2);
		}
		i++;
		cmd = cmd->next;
	}
	return (0);
}

void	print_error(char *msg, t_cmd *cmd)
{
	free_lst(&cmd);
	printf("%s", msg);
	ft_set_status(2);
}
