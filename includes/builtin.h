/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 05:30:04 by anclarma          #+#    #+#             */
/*   Updated: 2022/02/05 06:44:16 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "libft.h"

/*
** ft_cd.c
*/
int		ft_cd(int ac, char **av, t_list **env, int *fd);

/*
** ft_echo.c
*/
int		ft_echo(int ac, char **av, int *fd);

/*
** ft_pwd.c
*/
char	*alloc_pwd(void);
int		ft_pwd(int ac, char **av, int *fd);

/*
** ft_exit.c
*/
int		ft_exit(int ac, char **av, int status, int *fd);

/*
** ft_env.c
*/
int		ft_env(t_list *env, int *fd);

/*
** ft_export.c
*/
int		ft_export(int ac, char **av, t_list **env, int *fd);

/*
** ft_unset.c
*/
int		ft_unset(int ac, char **av, t_list **env, int *fd);

#endif
