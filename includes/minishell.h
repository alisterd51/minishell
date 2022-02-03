/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 06:34:19 by anclarma          #+#    #+#             */
/*   Updated: 2022/02/03 22:19:32 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "struct.h"

# define NONE			0
# define PIPELINE		1
# define COMMAND		2
# define ARGUMENT		3
# define AND			4
# define OR				5
# define S_LEFT			6
# define D_LEFT			7
# define D_LEFT_EXP		8
# define S_RIGHT		9
# define D_RIGHT		10
# define T_FILE			11
# define DELIMITOR		12
# define EXPEND			13
# define DOLLAR			14
# define DEFAULT_PS1	"\033[1;34mminishell-beta \033[1;32mv0.1\033[0m$ "
# define DEFAULT_PS2	"heredoc> "

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

/*
** init_list.c
*/
t_list	*init_env(char **env);

/*
** token_to_ast.c
*/
t_ast	*token_to_ast(t_cmd *lst_token);

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
** ft_heredoc.c
*/
int		ft_heredoc(int fd, char const *terminat);

/*
** ft_handler.c
*/
void	handler_int(int sig);
void	handler_int_heredoc(int sig);

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
int		is_redirect(int type);

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
