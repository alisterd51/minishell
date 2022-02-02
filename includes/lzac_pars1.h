/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lzac_pars1.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:51:26 by lzaccome          #+#    #+#             */
/*   Updated: 2022/02/02 02:34:27 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "struct.h"

enum e_type
{

	LZAC_NONE,		// default  0
	ARG,			// word     1
	CMD,			// cmd      2
	T_FILE,			// after < || > || << || >>  3
	DELIMITOR,		// after << 4
	REDIRECT_L,		// <        5
	REDIRECT_R,		// >        6
	HEREDOC,		// <<       7
	REDIRECT_ADD,	// >>       8
	PIPE
};

typedef struct s_cmd	t_cmd;
struct s_cmd 
{
	char		*word;
	enum e_type	type;
	int			space;
	t_cmd		*next;
};

typedef struct s_stuff	t_stuff;
struct s_stuff
{
	enum e_type	type;
	char		*str;
	int			space;
	int			i;
};

t_cmd	*get_cmd(char *str, char **envp);
int		ft_strclen(char *str, char c, int i);
char	*lzac_ft_strndup(char *str, int size, int i);
t_cmd	*parsing_shell(char *str, char **envp);
void	lzac_ft_lstadd_back(t_cmd **cmd, t_cmd *new);
t_cmd	*lzac_ft_lstnew(char *word, enum e_type type, int space);
void	free_lst(t_cmd **cmd);
void	get_type(t_cmd *cmd);
int	ft_strarglen(char *str, int i);
int	lzac_ft_lstsize(t_cmd *lst);
void		print_error(char *msg, t_cmd *cmd);
void	get_error(t_cmd *cmd);
void	ft_space(t_stuff *stuff, char *str);
char	*lzac_ft_strjoin(char *s1, char *s2);

t_ast	*token_to_ast(t_cmd *lst_token);
void	print_token(t_cmd *lst_token);

#endif
