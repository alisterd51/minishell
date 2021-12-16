/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:40:20 by anclarma          #+#    #+#             */
/*   Updated: 2021/12/15 21:41:01 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_end(int mode, int end)
{
	static int	last_end = 0;

	if (mode == 1)
		last_end = end;
	return (last_end);
}

int	ft_get_end(void)
{
	return (ft_end(0, 0));
}

void	ft_set_end(int end)
{
	ft_end(1, end);
	return ;
}
