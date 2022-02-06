/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 23:27:35 by lzaccome          #+#    #+#             */
/*   Updated: 2022/02/06 09:05:12 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lzac_pars1.h"
#include "minishell.h"

int	cond_type(t_cmd *tmp)
{
	if (tmp->next->type == S_LEFT || tmp->next->type == S_RIGHT
		|| tmp->next->type == D_RIGHT
		|| tmp->next->type == D_LEFT)
		return (1);
	return (0);
}

void	join_args(t_cmd **tmp)
{
	t_cmd	*tmp2;
	char	*tmp3;

	tmp3 = (*tmp)->word;
	(*tmp)->word = ft_strjoin((*tmp)->word, (*tmp)->next->word);
	free(tmp3);
	tmp2 = (*tmp)->next;
	(*tmp)->next = (*tmp)->next->next;
	free(tmp2->word);
	free(tmp2);
}

int	get_type(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp && tmp->next && (tmp->type == S_LEFT
				|| tmp->type == S_RIGHT || tmp->type == D_RIGHT))
		{
			if (cond_type(tmp))
				return (print_err_ret("redirection\n", cmd));
			else if (tmp->next->type == PIPELINE)
				return (print_err_ret("token `|'\n", cmd));
			tmp->next->type = T_FILE;
		}
		if (tmp->next && tmp->next->space == 0 && tmp->type == ARGUMENT
			&& tmp->next->type == ARGUMENT)
			join_args(&tmp);
		else
			tmp = tmp->next;
	}
	if (get_type2(cmd) == 2)
		return (2);
	return (0);
}

int	get_type2(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp && tmp->next && tmp->type == D_LEFT)
		{
			if (cond_type(tmp))
				return (print_err_ret("redirection\n", cmd));
			else if (tmp->next->type == PIPELINE)
				return (print_err_ret("token `|'\n", cmd));
			tmp->next->type = DELIMITOR;
		}
		tmp = tmp->next;
	}
	return (0);
}