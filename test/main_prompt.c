/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 23:00:19 by anclarma          #+#    #+#             */
/*   Updated: 2021/10/28 23:04:03 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

#define BUFFER_SIZE	1

int	main(int ac, char **av, char **env)
{
	ssize_t	ret;
	char	buf[BUFFER_SIZE];

	(void)ac;
	(void)av;
	(void)env;
	ret = 1;
	while (ret)
	{
		print_prompt(env);
		ret = read(0, buf, BUFFER_SIZE);
	}
	return (0);
}
