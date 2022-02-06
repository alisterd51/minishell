/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 23:23:32 by lzaccome          #+#    #+#             */
/*   Updated: 2022/02/06 13:47:03 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lzac_pars1.h"
#include "minishell.h"

void	free_lst(t_cmd **cmd)
{
	t_cmd	*tmp;
	t_cmd	*next;

	tmp = *cmd;
	while (tmp)
	{
		if (tmp->type != S_LEFT && tmp->type != S_RIGHT
			&& tmp->type != D_RIGHT && tmp->type != D_LEFT
			&& tmp->type != PIPELINE && tmp->type != DOLLAR)
			free(tmp->word);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	*cmd = NULL;
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
		if (cmd && cmd->next && cmd->type == PIPELINE
			&& cmd->next->type == PIPELINE)
			return (print_err_ret("`|'\n", tmp));
		if (i == 1 && cmd->type == PIPELINE)
			return (print_err_ret("`|'\n", tmp));
		if (i == size && (cmd->type == S_LEFT || cmd->type == S_RIGHT
				|| cmd->type == D_RIGHT || cmd->type == D_LEFT
				|| cmd->type == PIPELINE))
			return (print_err_ret("`newline'\n", tmp));
		i++;
		cmd = cmd->next;
	}
	return (0);
}

int	print_err_ret(char *msg, t_cmd *cmd)
{
	char	*error;

	error = "syntax error near unexpected token ";
	free_lst(&cmd);
	ft_putstr_fd(error, 2);
	ft_putstr_fd(msg, 2);
	ft_set_status(2);
	return (2);
}

int	print_error(char *msg, t_cmd **cmd)
{
	free_lst(cmd);
	ft_putstr_fd(msg, 2);
	ft_set_status(2);
	return (1);
}
