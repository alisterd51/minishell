/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lzac_pars1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 22:22:58 by lzaccome          #+#    #+#             */
/*   Updated: 2022/02/01 04:36:33 by anclarma         ###   ########.fr       */
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

t_cmd	*parsing_shell(char *str, char **envp)
{
	t_cmd	*cmd;

	(void)envp;
	cmd = get_cmd(str, envp);
	return (cmd);
}

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
