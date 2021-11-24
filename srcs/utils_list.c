/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 18:36:10 by anclarma          #+#    #+#             */
/*   Updated: 2021/11/24 20:55:40 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	**list_to_tab(t_list *lst_env)
{
	char	**env;
	size_t	size_env;
	size_t	i;

	size_env = (size_t)ft_lstsize(lst_env);
	i = 0;
	env = (char **)malloc(sizeof(char *) * (size_env + 1));
	while (i < size_env)
	{
		env[i] = ft_strdup((char *)lst_env->content);
		i++;
		lst_env = lst_env->next;
	}
	env[i] = NULL;
	return (env);
}
