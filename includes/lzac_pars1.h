/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lzac_pars1.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:51:26 by lzaccome          #+#    #+#             */
/*   Updated: 2022/02/06 09:44:54 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LZAC_PARS1_H
# define LZAC_PARS1_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "struct.h"

typedef struct s_stuff			t_stuff;
struct	s_stuff
{
	char	*str;
	int		type;
	int		space;
	int		i;
};

typedef struct s_expend_stuff	t_expend_stuff;
struct	s_expend_stuff
{
	t_cmd	**cmd;
	t_stuff	*stuff;
	char	**envp;
};

t_cmd	*get_cmd(char *str, char **envp);
int		ft_strclen(char *str, char c);
t_cmd	*parsing_shell(char *str, char **envp);
void	lzac_ft_lstadd_back(t_cmd **cmd, t_cmd *new);
t_cmd	*lzac_ft_lstnew(char *word, int type, int space);
void	free_lst(t_cmd **cmd);
int		get_type(t_cmd *cmd);
int		ft_strarglen(char *str);
int		lzac_ft_lstsize(t_cmd *lst);
void	print_error(char *msg, t_cmd *cmd);
int		get_error(t_cmd *cmd);
void	ft_space(t_stuff *stuff, char *str);
void	print_token(t_cmd *lst_token);
int		ft_expstrclen(char *str, char c);
int		ft_quote(t_stuff *stuff, char c, t_cmd **cmd);
void	expend_in_quote(char **envp, t_cmd **cmd, t_stuff *stuff);
void	ft_rdleft(t_stuff *stuff, t_cmd **cmd);
void	ft_rdright(t_stuff *stuff, t_cmd **cmd);
void	ft_alnum(t_stuff *stuff, t_cmd **cmd);
void	lzac_ft_pipe(t_stuff *stuff, t_cmd **cmd);
void	ft_expend(t_stuff *stuff, char **envp, t_cmd **cmd);
int		print_err_ret(char *msg, t_cmd *cmd);
int		get_type2(t_cmd *cmd);
int		get_cmd_exe(t_stuff *stuff, char *str, t_cmd **cmd, char **envp);
t_cmd	*ft_cmdlast(t_cmd *lst);
void	expend_step4(char *word, int *i, int *j, t_expend_stuff *st);
void	expend_step3(char *word, int i, int j, t_expend_stuff *st);
int		ft_cmdsize(t_cmd *lst);
void	expend_step2(t_cmd **cmd, t_cmd *tmp);
void	expend_step1(t_cmd *tmp, t_cmd *tmp_del);
char	*ft_expend_quote(char *word, int *i, char **envp);

#endif
