/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 06:34:19 by anclarma          #+#    #+#             */
/*   Updated: 2021/12/16 17:03:39 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include "struct.h"

# define NONE		0
# define PIPELINE	1
# define COMMAND	2
# define AND		3
# define OR			4
# define S_LEFT		5
# define D_LEFT		6
# define S_RIGHT	7
# define D_RIGHT	8

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
int		exec_ast(t_ast *ast, t_list **lst_env);

/*
** utils_ast.c
*/
char	**arg_to_tab(t_arg *arg);
int		tabsize(char **tab);
char	**line_to_tab(char *line);

/*
** utils_ast.c
*/
void	clean_tab(char ***tab);
char	**line_to_tab(char *line);

/*
** utils_list.c
*/
char	**list_to_tab(t_list *lst_env);

/*
** utils_list2.c
*/
int		tablen(char **tab);

/*
** ft_pipe.c
*/
int		ft_pipe(t_ast *ast, t_list **lst_env);

/*
** solve_path.c
*/
char	*solve_path(char *path, char *key);

/*
** ret_status.c
*/
int		ft_get_status(void);
void	ft_set_status(int status);

/*
** end_status.c
*/
int		ft_get_end(void);
void	ft_set_end(int status);

#endif
