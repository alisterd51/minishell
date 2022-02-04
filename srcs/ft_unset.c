/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 00:49:44 by anclarma          #+#    #+#             */
/*   Updated: 2022/02/05 00:17:18 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

static void	intern_unset(char *key, t_list **env)
{
	t_list	*node_env;
	t_list	*prev_env;
	t_list	*next_env;

	node_env = *env;
	prev_env = NULL;
	while (node_env)
	{
		if (!ft_strncmp(key, node_env->content, ft_strlen(key))
			&& ((char *)node_env->content)[ft_strlen(key)] == '=')
		{
			next_env = node_env->next;
			ft_lstdelone(node_env, free);
			if (prev_env == NULL)
				*env = next_env;
			else
				prev_env->next = next_env;
			return ;
		}
		prev_env = node_env;
		node_env = node_env->next;
	}
}

int	ft_unset(int ac, char **av, t_list **env)
{
	ac--;
	av++;
	while (ac > 0)
	{
		intern_unset(*av, env);
		ac--;
		av++;
	}
	return (0);
}
