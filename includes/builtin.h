/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 05:30:04 by anclarma          #+#    #+#             */
/*   Updated: 2022/01/03 16:58:30 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "libft.h"

/*
** ft_cd.c
*/
int		ft_cd(int ac, char **av, t_list **env);

/*
** ft_echo.c
*/
int		ft_echo(int ac, char **av);

/*
** ft_pwd.c
*/
char	*alloc_pwd(void);
int		ft_pwd(int ac, char **av);

/*
** ft_exit.c
*/
int		ft_exit(int ac, char **av, int status);

/*
** ft_env.c
*/
int		ft_env(t_list *env);

/*
** ft_export.c
*/
int		ft_export(int ac, char **av, t_list **env);

/*
** ft_unset.c
*/
int		ft_unset(int ac, char **av, t_list **env);

#endif
