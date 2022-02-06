/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 23:37:04 by lzaccome          #+#    #+#             */
/*   Updated: 2022/02/06 10:25:32 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lzac_pars1.h"
#include "minishell.h"

void	lzac_ft_pipe(t_stuff *stuff, t_cmd **cmd)
{
	t_cmd	*new;

	stuff->type = PIPELINE;
	new = lzac_ft_lstnew("|", stuff->type, stuff->space);
	lzac_ft_lstadd_back(cmd, new);
	stuff->i = stuff->i + 1;
}
