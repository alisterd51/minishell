/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ft_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 22:28:54 by anclarma          #+#    #+#             */
/*   Updated: 2021/10/28 22:29:10 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_list	*lst_env;
	int		ret;

	lst_env = init_env(env);
	ret = ft_export(ac - 1, av + 1, &lst_env);
	ft_env(lst_env);
	clean_env(&lst_env);
	return (ret);
}
