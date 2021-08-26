/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 04:07:34 by anclarma          #+#    #+#             */
/*   Updated: 2021/08/26 18:00:16 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_elem;
	int		error;

	new_lst = NULL;
	error = 0;
	while (lst && !error)
	{
		new_elem = ft_lstnew(f(lst->content));
		if (!new_elem)
			error = 1;
		ft_lstadd_back(&new_lst, new_elem);
		lst = lst->next;
	}
	if (error)
		ft_lstclear(&new_lst, del);
	return (new_lst);
}
