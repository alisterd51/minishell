/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_libft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 21:43:09 by anclarma          #+#    #+#             */
/*   Updated: 2021/10/28 21:43:22 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

static void	*init_content(void *content)
{
	return (ft_strdup(content));
}

static void	del_content(void *content)
{
	free(content);
}

static void	print_lst(t_list *lst)
{
	while (lst)
	{
		printf("%p: %s\n", (void *)lst, (char *)lst->content);
		lst = lst->next;
	}
}

int	main(int ac, char **av)
{
	t_list	*lst;
	t_list	*new_lst;

	lst = NULL;
	(void)ac;
	(void)av;
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("01234")));
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("56789")));
	new_lst = ft_lstmap(lst, &init_content, &del_content);
	print_lst(lst);
	print_lst(new_lst);
	ft_lstclear(&lst, &free);
	ft_lstclear(&new_lst, &free);
	return (0);
}
