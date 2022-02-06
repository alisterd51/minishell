/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lzac_pars2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 17:50:28 by lzaccome          #+#    #+#             */
/*   Updated: 2022/02/06 09:02:34 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lzac_pars1.h"
#include "minishell.h"

int	ft_isalnumsymb(int c)
{
	return (('0' <= c && c <= '9')
		|| ('A' <= c && c <= 'Z')
		|| ('a' <= c && c <= 'z') || c == '/'
		|| c == '-' || c == '.' || c == '%'
		|| c == '_' || c == '=' || c == '?'
		|| c == '*' || c == '-' || c == '+'
		|| c == '(' || c == ')' || c == '&'
		|| c == '^' || c == '#' || c == '@'
		|| c == '!' || c == ',' || c == '~'
		|| c == ';' || c == ':');
}

int	intern_get_cmd(char *str, t_stuff *stuff, t_cmd **cmd, char **envp)
{
	if (ft_isspace(str[stuff->i]))
		ft_space(stuff, str);
	if (str[stuff->i] == '\'' && ft_quote(stuff, '\'', cmd) == 1)
		return (1);
	else if (str[stuff->i] == '\"')
	{
		if (ft_quote(stuff, '\"', cmd) == 1)
			return (1);
		expend_in_quote(envp, cmd, stuff);
	}
	else if (str[stuff->i] == '<')
		ft_rdleft(stuff, cmd);
	else if (str[stuff->i] == '>')
		ft_rdright(stuff, cmd);
	else if (ft_isalnum(str[stuff->i]))
		ft_alnum(stuff, cmd);
	else if (str[stuff->i] == '|')
		lzac_ft_pipe(stuff, cmd);
	else if (str[stuff->i] == '$')
		ft_expend(stuff, envp, cmd);
	else if (stuff->space != 1)
		stuff->i = stuff->i + 1;
	return (0);
}

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
		if (intern_get_cmd(str, &stuff, &cmd, envp) == 1)
			return (NULL);
	}
	if (get_type(cmd) == 2)
		return (NULL);
	if (get_error(cmd) == 2)
		return (NULL);
	return (cmd);
}
