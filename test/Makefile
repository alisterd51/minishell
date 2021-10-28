# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/12 13:07:16 by anclarma          #+#    #+#              #
#    Updated: 2021/10/28 23:47:48 by anclarma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME1		= test_ast
NAME2		= test_echo
NAME3		= test_env
NAME4		= test_exit
NAME5		= test_export
NAME6		= test_pwd
NAME7		= test_libft
NAME8		= test_prompt
LIBFT		= ../libft/libft.a
C_FILES		= ft_echo.c						\
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
SRCS		= $(addprefix ../srcs/,$(C_FILES))

SRCS1		= $(SRCS)						\
			  main_ast.c
SRCS2		= $(SRCS)						\
			  main_ft_echo.c
SRCS3		= $(SRCS)						\
			  main_ft_env.c
SRCS4		= $(SRCS)						\
			  main_ft_exit.c
SRCS5		= $(SRCS)						\
			  main_ft_export.c
SRCS6		= $(SRCS)						\
			  main_ft_pwd.c
SRCS7		= $(SRCS)						\
			  main_libft.c

OBJS1		= $(SRCS1:.c=.o)
DEPS1		= $(OBJS1:.o=.d)
OBJS2		= $(SRCS2:.c=.o)
DEPS2		= $(OBJS2:.o=.d)
OBJS3		= $(SRCS3:.c=.o)
DEPS3		= $(OBJS3:.o=.d)
OBJS4		= $(SRCS4:.c=.o)
DEPS4		= $(OBJS4:.o=.d)
OBJS5		= $(SRCS5:.c=.o)
DEPS5		= $(OBJS5:.o=.d)
OBJS6		= $(SRCS6:.c=.o)
DEPS6		= $(OBJS6:.o=.d)
OBJS7		= $(SRCS7:.c=.o)
DEPS7		= $(OBJS7:.o=.d)

CC			= cc
CFLAGS		= -Wall -Wextra -Werror			\
			  -MMD -MP
CINCLUDES	= -I ../includes				\
			  -I ../libft/includes
CLIBS		= -L ../libft -lft -lreadline

all:		$(NAME1) $(NAME2) $(NAME3)		\
			$(NAME4) $(NAME5) $(NAME6)		\
			$(NAME7)

%.o:%.c
			$(CC) $(CFLAGS) $(CINCLUDES) -MMD -MP -c $< -o $@

$(NAME1):	$(LIBFT) $(OBJS1)
			$(CC) $(OBJS1) $(CFLAGS) $(CLIBS) -o $@

$(NAME2):	$(LIBFT) $(OBJS2)
			$(CC) $(OBJS2) $(CFLAGS) $(CLIBS) -o $@

$(NAME3):	$(LIBFT) $(OBJS3)
			$(CC) $(OBJS3) $(CFLAGS) $(CLIBS) -o $@

$(NAME4):	$(LIBFT) $(OBJS4)
			$(CC) $(OBJS4) $(CFLAGS) $(CLIBS) -o $@

$(NAME5):	$(LIBFT) $(OBJS5)
			$(CC) $(OBJS5) $(CFLAGS) $(CLIBS) -o $@

$(NAME6):	$(LIBFT) $(OBJS6)
			$(CC) $(OBJS6) $(CFLAGS) $(CLIBS) -o $@

$(NAME7):	$(LIBFT) $(OBJS7)
			$(CC) $(OBJS7) $(CFLAGS) $(CLIBS) -o $@

$(LIBFT):
			make -C ../libft all

clean:
			make -C ../libft fclean
			rm -f $(OBJS1) $(DEPS1)	\
				$(OBJS2) $(DEPS2)	\
				$(OBJS3) $(DEPS3)	\
				$(OBJS4) $(DEPS4)	\
				$(OBJS5) $(DEPS5)	\
				$(OBJS6) $(DEPS6)	\
				$(OBJS7) $(DEPS7)

fclean:		clean
			rm -f $(NAME1) $(NAME2) $(NAME3)	\
			$(NAME4) $(NAME5) $(NAME6) $(NAME7)

re:			fclean all

-include	$(DEPS)

.PHONY:		all check clean fclean re 
