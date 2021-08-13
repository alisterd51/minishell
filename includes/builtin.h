/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 05:30:04 by anclarma          #+#    #+#             */
/*   Updated: 2021/08/13 01:35:41 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

/*
** ft_echo.c
*/
int	ft_echo(int ac, char **av);

/*
** ft_cd.c
*/
int	ft_cd(int ac, char **av);

/*
** ft_pwd.c
*/
int	ft_pwd(int ac, char **av);

/*
** ft_export.c
*/
int	ft_export(int ac, char **av);

/*
** ft_unset.c
*/
int	ft_unset(int ac, char **av);

/*
** ft_env.c
*/
int	ft_env(int ac, char **av);

/*
** ft_exit.c
*/
int	ft_exit(int ac, char **av);

#endif
