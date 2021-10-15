/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 06:34:19 by anclarma          #+#    #+#             */
/*   Updated: 2021/10/15 15:12:19 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include "struct.h"

# define NONE		0
# define PIPELINE	1
# define COMMAND	2
# define S_LEFT		3
# define D_LEFT		4
# define S_RIGHT	5
# define D_RIGHT	6

/*
** init_list.c
*/
t_list	*init_env(char **env);

/*
** init_ast.c
*/
t_ast	*init_ast(int ac, char **av);

/*
** print_ast.c
*/
void	print_ast(t_ast *ast, int level);

/*
** clean_list.c
*/
void	clean_env(t_list **lst_env);

/*
** clean_ast.c
*/
void	clean_ast(t_ast **ast);

/*
** exec_ast.c
*/
int		exec_ast(t_ast *ast, char **env);

/*
** utils_ast.c
*/
char	**arg_to_tab(t_arg *arg);
void	clean_tab(char ***tab);

/*
** ft_pipe.c
*/
int		ft_pipe(t_ast *ast, char **env);

#endif
