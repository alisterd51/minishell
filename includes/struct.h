/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 06:34:19 by anclarma          #+#    #+#             */
/*   Updated: 2021/12/23 17:09:00 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_ast	t_ast;
struct	s_ast
{
	int		type;
	void	*paw1;
	void	*paw2;
};

typedef struct s_arg	t_arg;
struct	s_arg
{
	char	*arg;
	t_arg	*next;
};

typedef struct s_redir	t_redir;
struct	s_redir
{
	int		type;
	char	*file;
	t_redir	*next;
};

typedef struct s_cd		t_cd;
struct	s_cd
{
	char	*curpath;
	char	*operand;
	char	*new_pwd;
	t_list	**env;
	int		ret;
};

#endif
