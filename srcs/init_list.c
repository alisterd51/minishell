/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 18:36:10 by anclarma          #+#    #+#             */
/*   Updated: 2022/01/24 17:56:27 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

/*
** ajout des valeurs minimal:
** PWD=$(pwd)
** SHLVL=
** _=
*/
static void	minimal_env(t_list **list_env)
{
	t_list	*new_node;
	char	*new_content;

	new_content = ft_strdup("SHLVL=1");
	if (new_content)
		return ;
	new_node = ft_lstnew(new_content);
	if (new_node == NULL)
	{
		free(new_content);
		new_content = NULL;
		return ;
	}
	ft_lstadd_back(list_env, new_node);
}

t_list	*init_env(char **env)
{
	t_list	*list_env;
	t_list	*new_node;
	char	*new_content;

	list_env = NULL;
	if (*env == NULL)
		minimal_env(&list_env);
	while (*env)
	{
		new_content = ft_strdup(*env);
		new_node = ft_lstnew(new_content);
		if (new_node == NULL || new_content == NULL)
		{
			free(new_content);
			free(new_node);
			clean_env(&list_env);
			return (NULL);
		}
		ft_lstadd_back(&list_env, new_node);
		env++;
	}
	return (list_env);
}
