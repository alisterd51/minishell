/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 06:34:19 by anclarma          #+#    #+#             */
/*   Updated: 2022/01/23 01:57:18 by anclarma         ###   ########.fr       */
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
void	exec_ast(t_ast *ast, t_list **lst_env, int *status);

/*
** exec_builtin.c
*/
int		exec_builtin(char **tab, t_list **lst_env);

/*
** exec_redir.c
*/
int		exec_redir(t_redir *redir);

/*
** ft_pipe.c
*/
void	ft_pipe(t_ast *ast, t_list **lst_env, int *status);

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
** utils_builtin.c
*/
int		is_builtin(char *path);

/*
** utils_list.c
*/
char	**list_to_tab(t_list *lst_env);

/*
** utils_list2.c
*/
int		tablen(char **tab);

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

/*
** ft_cd_step1.c
*/
int		step0(t_cd *cd_arg);
int		step1(t_cd *cd_arg);
int		step2(t_cd *cd_arg);
int		step3(t_cd *cd_arg);
int		step4(t_cd *cd_arg);

/*
** ft_cd_step2.c
*/
int		step5(t_cd *cd_arg);
int		step6(t_cd *cd_arg);
int		step7(t_cd *cd_arg);
int		step8(t_cd *cd_arg);
int		step9(t_cd *cd_arg);

/*
** ft_cd_utils1.c
*/
int		test_home(t_list *env);
int		test_dot(char *operand);
int		test_dotdot(char *operand);
char	*get_subcdpath(char *cdpath);
char	*ft_concatenation(char *str1, char *str2, char *str3);
int		test_directory(char *path_dir);
int		test_option(char *option);
char	*clean_a(char *curpath);
char	*clean_b(char *curpath);
char	*clean_c(char *curpath);
char	*to_relative(char *curpath, char *operand);
char	*ft_getenv(char *key, t_list *lst_env);
void	ft_setenv(char *key, char *value, t_list **lst_env);
char	*pwd_p(void);

/*
** colector.c
*/
void	clean_colector(void);
void	to_clean_colector(t_ast **ast);

#endif
