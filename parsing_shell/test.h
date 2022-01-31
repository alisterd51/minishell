/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:51:26 by lzaccome          #+#    #+#             */
/*   Updated: 2022/01/21 02:52:28 by lzaccome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

enum e_type
{
	NONE,			// default  0
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
	// t_cmd		*prev;
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
int	ft_strclen(char *str, char c, int i);
void	ft_bzero(void *s, size_t n);
char *ft_strndup(char *str, int size, int i);
t_cmd	*parsing_shell(char *str, char **envp);
int	main(int ac, char **av, char **envp);
void	ft_lstadd_back(t_cmd **cmd, t_cmd *new);
t_cmd	*ft_lstnew(char *word, enum e_type type, int space);
void	free_lst(t_cmd **cmd);
char	*ft_strjoin(char *s1, char *s2);
int		ft_isspace(int c);
int		ft_isalnum(int c);
void	get_type(t_cmd *cmd);
int	ft_strarglen(char *str, int i);
int	ft_lstsize(t_cmd *lst);
void	print_error(char *msg, t_cmd *cmd);
void	get_error(t_cmd *cmd);
void	ft_space(t_stuff *stuff, char *str);
// void	init_stuff(t_stuff *stuff);

#endif
