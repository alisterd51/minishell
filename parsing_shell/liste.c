/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 17:50:28 by lzaccome          #+#    #+#             */
/*   Updated: 2022/01/31 23:40:28 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

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
			&& (*cmd)->type != PIPE)
			free((*cmd)->word);
		free(*cmd);
	}
}

t_cmd	*ft_lstnew(char *word, enum e_type type, int space)
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

void	ft_lstadd_back(t_cmd **cmd, t_cmd *new)
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

int	ft_lstsize(t_cmd *lst)
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

void	ft_quote(t_stuff *stuff, char c, t_cmd **cmd)
{
	t_cmd	*new;
	char	*word;
	int		j;

	j = 0;
	stuff->i++;
	j = ft_strclen(stuff->str, c, stuff->i);
	word = ft_strndup(stuff->str, j, stuff->i);
	new = ft_lstnew(word, ARG, stuff->space);
	ft_lstadd_back(cmd, new);
	stuff->i += j + 1;
}

void	ft_alnum(t_stuff *stuff, t_cmd **cmd)
{
	int		j;
	char	*word;
	t_cmd	*new;

	j = 0;
	stuff->type = ARG;
	j = ft_strarglen(stuff->str, stuff->i);
	word = ft_strndup(stuff->str, j, stuff->i);
	new = ft_lstnew(word, stuff->type, stuff->space);
	ft_lstadd_back(cmd, new);
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
		new = ft_lstnew("<<", stuff->type, stuff->space);
		stuff->i++;
	}
	else
		new = ft_lstnew("<", stuff->type, stuff->space);
	ft_lstadd_back(cmd, new);
}

void	ft_rdright(t_stuff *stuff, t_cmd **cmd)
{
	t_cmd	*new;

	stuff->i++;
	stuff->type = REDIRECT_R;
	if (stuff->str[stuff->i] && stuff->str[stuff->i] == '>')
	{
		stuff->type = REDIRECT_ADD;
		new = ft_lstnew(">>", stuff->type, stuff->space);
		stuff->i++;
	}
	else
		new = ft_lstnew(">", stuff->type, stuff->space);
	ft_lstadd_back(cmd, new);
}

void	ft_pipe(t_stuff *stuff, t_cmd **cmd)
{
	t_cmd	*new;

	stuff->type = PIPE;
	new = ft_lstnew("|", stuff->type, stuff->space);
	ft_lstadd_back(cmd, new);
	stuff->i++;
}

void	init_stuff(t_stuff *stuff, char *str)
{	
	stuff->str = str;
	stuff->i = 0;
	stuff->space = 0;
	stuff->type = NONE;
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
		stuff.type = NONE;
		stuff.space = 0;
		if (ft_isspace(str[stuff.i]))
			ft_space(&stuff, str);
		if (str[stuff.i] == '\'')
			ft_quote(&stuff, '\'', &cmd);
		else if (str[stuff.i] == '\"')
			ft_quote(&stuff, '\"', &cmd);
		else if (str[stuff.i] == '<')
			ft_rdleft(&stuff, &cmd);
		else if (str[stuff.i] == '>')
			ft_rdright(&stuff, &cmd);
		else if (ft_isalnum(str[stuff.i]) || str[stuff.i] == '/'
			|| str[stuff.i] == '-')
			ft_alnum(&stuff, &cmd);
		else if (str[stuff.i] == '|')
			ft_pipe(&stuff, &cmd);
		else
		{
			if (stuff.space != 1)
				stuff.i++;
		}
	}
	get_type(cmd);
	get_error(cmd);
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
				|| tmp->type == REDIRECT_R || tmp->type == REDIRECT_ADD
				|| tmp->type == PIPE))
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
			tmp->word = ft_strjoin(tmp->word, tmp->next->word);
			tmp2 = tmp->next;
			tmp->next = tmp->next->next;
			free(tmp2->word);
			free(tmp2);
		}
		else
			tmp = tmp->next;
	}
}

void	get_error(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		size;
	int		i;

	tmp = cmd;
	size = ft_lstsize(cmd);
	i = 1;
	while (cmd)
	{
		if (i == 1 && cmd->type == PIPE)
			print_error("syntax error near unexpected token `|'\n", tmp);
		if (i == size && (cmd->type == REDIRECT_L || cmd->type == REDIRECT_R
				|| cmd->type == REDIRECT_ADD || cmd->type == HEREDOC))
			print_error("syntax error near unexpected token `newline'\n", tmp);
		i++;
		cmd = cmd->next;
	}
	return ;
}

void	print_error(char *msg, t_cmd *cmd)
{
	free_lst(&cmd);
	printf("%s", msg);
	return (2);
}
