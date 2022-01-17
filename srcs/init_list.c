/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 18:36:10 by anclarma          #+#    #+#             */
/*   Updated: 2021/12/19 17:17:55 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/*
** ajout des valeurs minimal:
** PWD=$(pwd)
** SHLVL=
** _=
*/
static void	minimal_env(t_list **list_env)
{
	ft_lstadd_back(list_env, ft_lstnew(ft_strdup("SHLVL=1")));
}

t_list	*init_env(char **env)
{
	t_list	*list_env;

	list_env = NULL;
	if (*env == NULL)
		minimal_env(&list_env);
	while (*env)
	{
		ft_lstadd_back(&list_env, ft_lstnew(ft_strdup(*env)));
		env++;
	}
	return (list_env);
}
