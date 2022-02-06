/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 23:13:38 by lzaccome          #+#    #+#             */
/*   Updated: 2022/02/06 09:00:47 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lzac_pars1.h"
#include "minishell.h"

void	expend_in_quote(char **envp, t_cmd **cmd, t_stuff *stuff)
{
	t_cmd			*tmp;
	t_cmd			*tmp_del;
	int				ij[2];
	t_expend_stuff	st;

	st = (t_expend_stuff){.cmd = cmd, .stuff = stuff, .envp = envp};
	ij[0] = 0;
	ij[1] = 0;
	tmp = ft_cmdlast(*cmd);
	tmp_del = *cmd;
	while (tmp_del && tmp_del->next && tmp_del->next->next)
		tmp_del = tmp_del->next;
	while (tmp && tmp->word && tmp->word[ij[0]] && !(tmp->word[ij[0]] == '$'
			&& (tmp->word[ij[0] + 1] != ' ' || tmp->word[ij[0] + 1] != '|')))
		ij[0]++;
	if (tmp && ij[0] == (int)ft_strlen(tmp->word))
		return ;
	expend_step4(tmp->word, ij + 0, ij + 1, &st);
	if (ij[1] < ij[0])
		expend_step3(tmp->word, ij[0], ij[1], &st);
	if (ft_cmdsize(*cmd) - 1 == 0)
		expend_step2(cmd, tmp);
	else
		expend_step1(tmp, tmp_del);
	return ;
}
