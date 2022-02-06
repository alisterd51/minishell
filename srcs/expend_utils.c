/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 08:49:11 by anclarma          #+#    #+#             */
/*   Updated: 2022/02/06 13:37:12 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lzac_pars1.h"
#include "minishell.h"

void	expend_step1(t_cmd *tmp, t_cmd *tmp_del)
{
	tmp = tmp_del->next;
	if (tmp_del->next != NULL)
		tmp_del->next = tmp_del->next->next;
	if (tmp != NULL)
		free(tmp->word);
	free(tmp);
}

void	expend_step2(t_cmd **cmd, t_cmd *tmp)
{
	*cmd = (*cmd)->next;
	if (tmp != NULL)
		free(tmp->word);
	free(tmp);
}

void	expend_step3(char *word, int i, int j, t_expend_stuff *st)
{
	char	*first;
	t_cmd	*new;

	first = ft_strndup(word + j, i - j);
	new = lzac_ft_lstnew(first, ARGUMENT, st->stuff->space);
	if (new == NULL)
		free(first);
	lzac_ft_lstadd_back(st->cmd, new);
}

void	sub_expend_step4(char *word, t_stuff *stuff, t_cmd **cmd)
{
	t_cmd	*new;

	new = lzac_ft_lstnew(word, ARGUMENT, stuff->space);
	if (new == NULL)
		free(word);
	lzac_ft_lstadd_back(cmd, new);
	stuff->space = 0;
}

void	expend_step4(char *word, int *i, int *j, t_expend_stuff *st)
{
	char	*first;
	char	*sec;

	while (word[*i])
	{
		if (word[*i] == '$' && (word[*i + 1] != ' ' || word[*i + 1] != '|'))
		{
			first = ft_strndup(word + *j, *i - *j);
			if (first && first[0] != 0)
				sub_expend_step4(first, st->stuff, st->cmd);
			else
				free(first);
			sec = ft_expend_quote(word, i, st->envp);
			if (sec != NULL)
				sub_expend_step4(sec, st->stuff, st->cmd);
			*j = *i;
		}
		else
			*i = *i + 1;
	}
}
