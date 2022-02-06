/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 23:34:44 by lzaccome          #+#    #+#             */
/*   Updated: 2022/02/05 23:35:35 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lzac_pars1.h"
#include "minishell.h"

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
	if (new == NULL)
		free(word);
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
	if (new == NULL)
		free(word);
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
