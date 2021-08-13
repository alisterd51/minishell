# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/12 13:07:16 by anclarma          #+#    #+#              #
#    Updated: 2021/08/13 02:03:22 by anclarma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
C_FILES		= main.c						\
			  ft_echo.c						\
			  ft_cd.c						\
			  ft_pwd.c						\
			  ft_export.c					\
			  ft_unset.c					\
			  ft_env.c						\
			  ft_exit.c
SRCS		= $(addprefix srcs/,$(C_FILES))
OBJS		= $(SRCS:.c=.o)
DEPS		= $(OBJS:.o=.d)
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
CINCLUDES	= -I ./includes					\
			  -I ./libft/includes
CLIBS		= -L ./libft -lft

all:		$(NAME)

%.o:%.c
			$(CC) $(CFLAGS) $(CINCLUDES) -MMD -MP -c $< -o $@

$(NAME):	sub_make $(OBJS)
			$(CC) $(OBJS) $(CFLAGS) $(CLIBS) -o $@

sub_make:
			make -C libft all

clean:
			make -C libft fclean
			rm -f $(OBJS) $(DEPS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

-include	$(DEPS)

.PHONY:		all clean fclean re
