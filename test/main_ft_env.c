/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ft_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 22:24:39 by anclarma          #+#    #+#             */
/*   Updated: 2021/10/28 22:24:50 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_list	*lst_env;
	int		ret;

	(void)ac;
	(void)av;
	lst_env = init_env(env);
	ret = ft_env(lst_env);
	clean_env(&lst_env);
	return (ret);
}
