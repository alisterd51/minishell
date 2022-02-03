/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lzac_pars1.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:51:26 by lzaccome          #+#    #+#             */
/*   Updated: 2022/02/03 22:17:39 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LZAC_PARS1_H
# define LZAC_PARS1_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "struct.h"

typedef struct s_stuff	t_stuff;
struct	s_stuff
{
	char	*str;
	int		type;
	int		space;
	int		i;
};

t_cmd	*get_cmd(char *str, char **envp);
int		ft_strclen(char *str, char c);
t_cmd	*parsing_shell(char *str, char **envp);
void	lzac_ft_lstadd_back(t_cmd **cmd, t_cmd *new);
t_cmd	*lzac_ft_lstnew(char *word, int type, int space);
void	free_lst(t_cmd **cmd);
void	get_type(t_cmd *cmd);
int		ft_strarglen(char *str);
int		lzac_ft_lstsize(t_cmd *lst);
void	print_error(char *msg, t_cmd *cmd);
int		get_error(t_cmd *cmd);
void	ft_space(t_stuff *stuff, char *str);
void	print_token(t_cmd *lst_token);
int		ft_expstrclen(char *str, char c);

#endif
