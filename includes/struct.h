/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 06:34:19 by anclarma          #+#    #+#             */
/*   Updated: 2022/02/03 22:18:03 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <sys/types.h>
# include "libft.h"

typedef struct s_ast			t_ast;
struct	s_ast
{
	int		type;
	void	*paw1;
	void	*paw2;
};

typedef struct s_arg			t_arg;
struct	s_arg
{
	char	*arg;
	t_arg	*next;
};

typedef struct s_redir			t_redir;
struct	s_redir
{
	int		type;
	char	*file;
	t_redir	*next;
};

typedef struct s_cd				t_cd;
struct	s_cd
{
	char	*curpath;
	char	*operand;
	char	*new_pwd;
	t_list	**env;
	int		ret;
};

typedef struct s_intern_pipe	t_intern_pipe;
struct	s_intern_pipe
{
	t_ast	*ast;
	t_list	**lst_env;
	int		*status;
	int		fd[2];
	pid_t	pid;
};

typedef struct s_cmd			t_cmd;
struct	s_cmd
{
	char	*word;
	int		type;
	int		space;
	t_cmd	*next;
};

#endif
