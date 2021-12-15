/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 18:36:10 by anclarma          #+#    #+#             */
/*   Updated: 2021/12/15 18:53:53 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/*
** ajout des valeurs minimal:
** PWD=$(pwd)
** HLVL=
** _=
*/

t_list	*init_env(char **env)
{
	t_list	*list_env;

	list_env = NULL;
	while (*env)
	{
		ft_lstadd_back(&list_env, ft_lstnew(ft_strdup(*env)));
		env++;
	}
	return (list_env);
}
