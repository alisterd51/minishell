/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:40:20 by anclarma          #+#    #+#             */
/*   Updated: 2021/11/23 09:51:49 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_status(int mode, int status)
{
	static int	last_status = 0;

	if (mode == 1)
		last_status = status;
	return (last_status);
}

int	ft_get_status(void)
{
	return (ft_status(0, 0));
}

void	ft_set_status(int status)
{
	ft_status(1, status);
	return ;
}
