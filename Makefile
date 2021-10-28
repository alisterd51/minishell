# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/12 13:07:16 by anclarma          #+#    #+#              #
#    Updated: 2021/10/28 23:47:18 by anclarma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
LIBFT		= libft/libft.a
C_FILES		= main.c						\
			  ft_echo.c						\
			  ft_pwd.c						\
			  ft_exit.c						\
			  ft_env.c						\
			  ft_export.c					\
			  ft_pipe.c						\
			  init_ast.c					\
			  print_ast.c					\
			  clean_ast.c					\
			  utils_ast.c					\
			  exec_ast.c					\
			  init_list.c					\
			  clean_list.c
SRCS		= $(addprefix srcs/,$(C_FILES))
OBJS		= $(SRCS:.c=.o)
DEPS		= $(OBJS:.o=.d)
CC			= cc
CFLAGS		= -Wall -Wextra -Werror			\
			  -MMD -MP
CINCLUDES	= -I ./includes					\
			  -I ./libft/includes
CLIBS		= -L ./libft -lft -lreadline

all:		$(NAME)

check:		all
			@test/run_tests.sh

%.o:%.c
			$(CC) $(CFLAGS) $(CINCLUDES) -MMD -MP -c $< -o $@

$(NAME):	$(LIBFT) $(OBJS)
			$(CC) $(OBJS) $(CFLAGS) $(CLIBS) -o $@

$(LIBFT):
			make -C libft all

clean:
			make -C libft fclean
			make -C test fclean
			rm -f $(OBJS) $(DEPS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

-include	$(DEPS)

.PHONY:		all check clean fclean re 
