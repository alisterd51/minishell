/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 22:57:41 by anclarma          #+#    #+#             */
/*   Updated: 2021/10/28 23:02:32 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include "libft.h"

void	print_prompt(char **env)
{
	static char	*prompt = NULL;

	(void)env;
	if (prompt == NULL)
		prompt = "minishell-beta-0.1$ ";
	write(1, prompt, ft_strlen(prompt));
}
