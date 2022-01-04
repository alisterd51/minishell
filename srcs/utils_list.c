/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 18:36:10 by anclarma          #+#    #+#             */
/*   Updated: 2022/01/04 06:59:47 by anclarma         ###   ########.fr       */
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

char	*ft_getenv(char *key, t_list *lst_env)
{
	while (lst_env)
	{
		if (!ft_strncmp(key, lst_env->content, ft_strlen(key)))
			return (ft_strdup((char *)lst_env->content + ft_strlen(key)));
		lst_env = lst_env->next;
	}
	return (NULL);
}

void	ft_setenv(char *key, char *value, t_list **lst_env)
{
	t_list	*env;
	char	*new_keyvalue;

	env = *lst_env;
	new_keyvalue = ft_strjoin(key, value);
	while (env)
	{
		if (!ft_strncmp(key, env->content, ft_strlen(key)))
		{
			free(env->content);
			env->content = new_keyvalue;
			return ;
		}
		env = env->next;
	}
	ft_lstadd_back(lst_env, ft_lstnew(new_keyvalue));
}
