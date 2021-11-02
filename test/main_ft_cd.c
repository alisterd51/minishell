/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ft_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 01:51:46 by anclarma          #+#    #+#             */
/*   Updated: 2021/11/02 04:52:43 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "builtin.h"
#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_list	*lst_env;
	int		ret;
	char	buf[1024];

	printf("%s\n", getcwd(buf, 1024));
	lst_env = init_env(env);
	ret = ft_cd(ac, av, &lst_env);
	clean_env(&lst_env);
	printf("%s\n", getcwd(buf, 1024));
	return (ret);
}
