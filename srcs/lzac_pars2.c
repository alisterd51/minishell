/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lzac_pars2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 17:50:28 by lzaccome          #+#    #+#             */
/*   Updated: 2022/02/03 10:10:59 by lzaccome         ###   ########.fr       */
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
		if ((*cmd)->type != S_LEFT && (*cmd)->type != S_RIGHT
			&& (*cmd)->type != D_RIGHT && (*cmd)->type != D_LEFT
			&& (*cmd)->type != PIPELINE && (*cmd)->type != DOLLAR)
			free((*cmd)->word);
		free(*cmd);
	}
}

t_cmd	*lzac_ft_lstnew(char *word, int type, int space)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	if (cmd == NULL)
		return (NULL);
	*cmd = (t_cmd){.word = word, .type = type, .space = space};
	return (cmd);
}

void	lzac_ft_lstadd_back(t_cmd **cmd, t_cmd *new)
{
	while (*cmd)
		cmd = &((*cmd)->next);
	*cmd = new;
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
	j = ft_strclen(stuff->str + stuff->i, c);
	if (j < 0)
	{
		print_error("unclosed quote\n", *cmd);
		return (1);
	}
	word = ft_strndup(stuff->str + stuff->i, j);
	new = lzac_ft_lstnew(word, ARGUMENT, stuff->space);
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
	stuff->type = ARGUMENT;
	j = ft_strarglen(stuff->str + stuff->i);
	word = ft_strndup(stuff->str + stuff->i, j);
	new = lzac_ft_lstnew(word, stuff->type, stuff->space);
	lzac_ft_lstadd_back(cmd, new);
	stuff->i += j;
}

void	ft_rdleft(t_stuff *stuff, t_cmd **cmd)
{
	t_cmd	*new;

	stuff->i++;
	stuff->type = S_LEFT;
	if (stuff->str[stuff->i] && stuff->str[stuff->i] == '<')
	{
		stuff->type = D_LEFT;
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
	stuff->type = S_RIGHT;
	if (stuff->str[stuff->i] && stuff->str[stuff->i] == '>')
	{
		stuff->type = D_RIGHT;
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

	stuff->type = PIPELINE;
	new = lzac_ft_lstnew("|", stuff->type, stuff->space);
	lzac_ft_lstadd_back(cmd, new);
	stuff->i++;
}

char	*search_env(char **envp, char *word)
{
	int		i;
	char	*str;
	char	*key;

	i = 0;
	str = NULL;
	if (!envp)
		return (NULL);
	key = ft_strjoin(word, "=");
	free(word);
	while (envp[i] && ft_strncmp(envp[i], key, ft_strlen(key)) != 0)
		i++;
	if (envp[i] && (ft_strncmp(envp[i], key, ft_strlen(key)) == 0))
	{
		printf("%s\n", envp[i]);
		str = envp[i];
		str = str + ft_strlen(key);
		free(key);
		return (ft_strdup(str));
	}
	free(key);
	return (NULL);
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
	j = ft_expstrclen(stuff->str + stuff->i, ' ');
	if (j == 0)
	{
		word = "$";
		stuff->type = DOLLAR;
	}
	else
	{
		word = ft_strndup(stuff->str + stuff->i, j);
		word = search_env(envp, word);
		if (word == NULL)
		{
			stuff->i++;
			free(word);
			return ;
		}
	}
	new = lzac_ft_lstnew(word, stuff->type, stuff->space);
	lzac_ft_lstadd_back(cmd, new);
		stuff->i += j;
}

// void	expend_in_quote(t_stuff *stuff, char **envp, t_cmd **cmd)
// {
// 	t_cmd	*tmp;
// 	int i;

// 	i = 0;
// 	tmp = *cmd;
// 	while (tmp->next)
// 		tmp = tmp->next;
// 	while (tmp->word[i])
// 	{
// 		if (tmp->word[i] == '$')
// 			ft_expend(stuff, envp, cmd);
// 		i++;
// 	}
// }

t_cmd	*get_cmd(char *str, char **envp)
{
	t_cmd		*cmd;
	t_stuff		stuff;

	cmd = NULL;
	stuff = (t_stuff){.str = str, .type = NONE};
	while (str[stuff.i])
	{
		stuff.type = NONE;
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
			// expend_in_quote(&stuff, envp, &cmd);
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
	char	*tmp3;

	tmp = cmd;
	while (tmp)
	{
		if (tmp && tmp->next && (tmp->type == S_LEFT
				|| tmp->type == S_RIGHT || tmp->type == D_RIGHT))
		{
			if (tmp->next->type == S_LEFT || tmp->next->type == S_RIGHT
				|| tmp->next->type == D_RIGHT
				|| tmp->next->type == D_LEFT)
				print_error("syntax error near unexpected token redirection\n", cmd);
			else if (tmp->next->type == PIPELINE)
				print_error("syntax error near unexpected token `|'\n", cmd);
			tmp->next->type = T_FILE;
		}
		if (tmp && tmp->next && tmp->type == D_LEFT)
		{
			if (tmp->next->type == S_LEFT || tmp->next->type == S_RIGHT
				|| tmp->next->type == D_RIGHT
				|| tmp->next->type == D_LEFT)
				print_error("syntax error near unexpected token redirection\n", cmd);
			else if (tmp->next->type == PIPELINE)
				print_error("syntax error near unexpected token `|'\n", cmd);
			tmp->next->type = DELIMITOR;
		}
		if (tmp->next && tmp->next->space == 0 && tmp->type == ARGUMENT
			&& tmp->next->type == ARGUMENT)
		{
			tmp3 = tmp->word;
			tmp->word = ft_strjoin(tmp->word, tmp->next->word);
			free(tmp3);
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
		if (cmd && cmd->next && cmd->type == PIPELINE && cmd->next->type == PIPELINE)
		{
			print_error("syntax error near unexpected token `|'\n", tmp);
			return (2);
		}
		if (i == 1 && cmd->type == PIPELINE)
		{
			print_error("syntax error near unexpected token `|'\n", tmp);
			return (2);
		}
		if (i == size && (cmd->type == S_LEFT || cmd->type == S_RIGHT
				|| cmd->type == D_RIGHT || cmd->type == D_LEFT || cmd->type == PIPELINE))
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
	ft_putstr_fd(msg, 2);
	ft_set_status(2);
}
