/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 23:20:21 by lzaccome          #+#    #+#             */
/*   Updated: 2022/02/05 23:20:42 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lzac_pars1.h"
#include "minishell.h"

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
