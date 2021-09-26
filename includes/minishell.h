/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 06:34:19 by anclarma          #+#    #+#             */
/*   Updated: 2021/09/26 18:33:49 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"

/*
** test ast
*/

typedef enum e_ast_type	t_ast_type;
enum	e_ast_type
{
	PIPELINE = 0,
	COMMAND = 1
};

typedef enum e_red_type	t_red_type;
enum	e_red_type
{
	S_LEFT = 0,
	D_LEFT = 1,
	S_RIGHT = 2,
	D_RIGHT = 3
};

typedef struct s_ast	t_ast;
struct	s_ast
{
	t_ast_type	type;
	void		*paw1;
	void		*paw2;
};

typedef struct s_arg	t_arg;
struct	s_arg
{
	char		*arg;
	t_arg		*next;
};

typedef struct s_redir	t_redir;
struct	s_redir
{
	t_red_type	type;
	char		*file;
	t_redir		*next;
};

//un pipe a 2 pattes (commande ou pipe)
//une commande a 2 pattes (argument et redirection)
//argument est un tableau ou une list et contient des char *
//redirection est un tableau ou une list et contient des redict_type
//redict_type contient un type et un char *

/*
** init_list.c
*/
t_list	*init_env(char **env);

/*
** clean_list.c
*/
void	clean_env(t_list **lst_env);

#endif
