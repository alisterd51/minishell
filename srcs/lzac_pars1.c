/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lzac_pars1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 22:22:58 by lzaccome          #+#    #+#             */
/*   Updated: 2022/02/05 08:41:58 by lzaccome         ###   ########.fr       */
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
	while (str[i] && str[i] != c && str[i] != '|' && str[i] != '\''
		&& str[i] != '"' && str[i] != '$')
		i++;
	return (i);
}

int	ft_strarglen(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '<' && str[i] != '>' && str[i] != '|'
		&& str[i] != ' ' && str[i] != '\'' && str[i] != '\"' && str[i] != '$')
		i++;
	return (i);
}

t_cmd	*parsing_shell(char *str, char **envp)
{
	t_cmd	*cmd;

	cmd = get_cmd(str, envp);
	return (cmd);
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

// int	ft_isalnum(int c)
// {
// 	return (('0' <= c && c <= '9')
// 		|| ('A' <= c && c <= 'Z')
// 		|| ('a' <= c && c <= 'z') || c == '/'
// 		|| c == '-' || c == '.' || c == '%'
// 		|| c == '_' || c == '=' || c == '?'
// 		|| c == '*' || c == '-' || c == '+'
// 		|| c == '(' || c == ')' || c == '&'
// 		|| c == '^' || c == '#' || c == '@'
// 		|| c == '!' || c == ',' || c == '~'
// 		|| c == ';' || c == ':');
// }
