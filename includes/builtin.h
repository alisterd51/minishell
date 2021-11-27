/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 05:30:04 by anclarma          #+#    #+#             */
/*   Updated: 2021/11/27 00:49:08 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "libft.h"

/*
** ft_cd.c
*/
int	ft_cd(int ac, char **av, t_list **env);

/*
** ft_echo.c
*/
int	ft_echo(int ac, char **av);

/*
** ft_pwd.c
*/
int	ft_pwd(int ac, char **av);

/*
** ft_exit.c
*/
int	ft_exit(int ac, char **av, int status);

/*
** ft_env.c
*/
int	ft_env(t_list *env);

/*
** ft_export.c
*/
int	ft_export(int ac, char **av, t_list **env);

/*
** ft_unset.c
*/
int	ft_unset(int ac, char **av, t_list **env);

#endif
