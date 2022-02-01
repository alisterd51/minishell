# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anclarma <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/01 19:41:40 by anclarma          #+#    #+#              #
#    Updated: 2022/01/29 15:02:51 by anclarma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME1		= test_ast
NAME2		= test_echo
NAME3		= test_env
NAME4		= test_exit
NAME5		= test_export
NAME6		= test_pwd
NAME7		= test_libft
NAME8		= test_cd
NAME9		= test_solve_path
LIBFT		= ../libft/libft.a 
C_DIR		= ../srcs
O_DIR		= ../objs
C_FILES		= main.c					\
			  ft_cd.c					\
			  ft_cd_step1.c				\
			  ft_cd_step2.c				\
			  ft_cd_utils1.c			\
			  ft_cd_utils2.c			\
			  ft_cd_utils3.c			\
			  ft_echo.c					\
			  ft_pwd.c					\
			  ft_exit.c					\
			  ft_env.c					\
			  ft_export.c				\
			  ft_unset.c				\
			  init_ast.c				\
			  print_ast.c				\
			  clean_ast.c				\
			  utils_ast.c				\
			  utils_builtin.c			\
			  utils_tab.c				\
			  utils_tab2.c				\
			  utils_list.c				\
			  exec_ast.c				\
			  exec_builtin.c			\
			  exec_redir.c				\
			  ft_heredoc.c				\
			  ft_handler.c				\
			  ft_pipe.c					\
			  init_list.c				\
			  clean_list.c				\
			  solve_path.c				\
			  ret_status.c				\
			  end_status.c				\
			  colector.c
SRCS		= $(patsubst %, $(C_DIR)/%, $(C_FILES))
SRCS1		= main_ast.c
SRCS2		= main_ft_echo.c
SRCS3		= main_ft_env.c
SRCS4		= main_ft_exit.c
SRCS5		= main_ft_export.c
SRCS6		= main_ft_pwd.c
SRCS7		= main_libft.c
SRCS8		= main_ft_cd.c
SRCS9		= main_solve_path.c
O_FILES		= $(C_FILES:.c=.o)
OBJS		= $(patsubst %, $(O_DIR)/%, $(O_FILES))
OBJS1		= $(SRCS1:.c=.o)
OBJS2		= $(SRCS2:.c=.o)
OBJS3		= $(SRCS3:.c=.o)
OBJS4		= $(SRCS4:.c=.o)
OBJS5		= $(SRCS5:.c=.o)
OBJS6		= $(SRCS6:.c=.o)
OBJS7		= $(SRCS7:.c=.o)
OBJS8		= $(SRCS8:.c=.o)
OBJS9		= $(SRCS9:.c=.o)
CC			= gcc
CXX			= g++
MAKE		= make
RM			= rm -f
MKDIR		= mkdir -p
CFLAGS		= -Wall -Wextra -Werror		\
			  -Wconversion				\
			  -Wpedantic				\
			  -pedantic-errors			\
			  -std=c99					\
			  -MMD -MP
CXXFLAGS	= -Wall -Wextra -Werror		\
			  -std=c++98				\
			  -MMD -MP
LFLAGS		= -Wall -Wextra -Werror
CINCLUDES	= -I ../includes			\
			  -I ../libft/includes
CLIBS		= -L ../libft -lft -lreadline

all:		$(NAME1) $(NAME2) $(NAME3)	\
			$(NAME4) $(NAME5) $(NAME6)	\
			$(NAME7) $(NAME8) $(NAME9)

check:		all

./%.o: ./%.c
			$(CC) $(CFLAGS) $(CINCLUDES) -c $< -o $@

$(O_DIR)/%.o: $(C_DIR)/%.c
			$(CC) $(CFLAGS) $(CINCLUDES) -c $< -o $@

$(O_DIR)/%.o: $(C_DIR)/%.cpp
			$(CXX) $(CXXFLAGS) $(CINCLUDES) -c $< -o $@

$(NAME1):	$(LIBFT) $(O_DIR) $(OBJS) $(OBJS1)
			$(CC) $(OBJS) $(OBJS1) $(CFLAGS) $(CLIBS) -o $@

$(NAME2):	$(LIBFT) $(O_DIR) $(OBJS) $(OBJS2)
			$(CC) $(OBJS) $(OBJS2) $(CFLAGS) $(CLIBS) -o $@

$(NAME3):	$(LIBFT) $(O_DIR) $(OBJS) $(OBJS3)
			$(CC) $(OBJS) $(OBJS3) $(CFLAGS) $(CLIBS) -o $@

$(NAME4):	$(LIBFT) $(O_DIR) $(OBJS) $(OBJS4)
			$(CC) $(OBJS) $(OBJS4) $(CFLAGS) $(CLIBS) -o $@

$(NAME5):	$(LIBFT) $(O_DIR) $(OBJS) $(OBJS5)
			$(CC) $(OBJS) $(OBJS5) $(CFLAGS) $(CLIBS) -o $@

$(NAME6):	$(LIBFT) $(O_DIR) $(OBJS) $(OBJS6)
			$(CC) $(OBJS) $(OBJS6) $(CFLAGS) $(CLIBS) -o $@

$(NAME7):	$(LIBFT) $(O_DIR) $(OBJS) $(OBJS7)
			$(CC) $(OBJS) $(OBJS7) $(CFLAGS) $(CLIBS) -o $@

$(NAME8):	$(LIBFT) $(O_DIR) $(OBJS) $(OBJS8)
			$(CC) $(OBJS) $(OBJS8) $(CFLAGS) $(CLIBS) -o $@

$(NAME9):	$(LIBFT) $(O_DIR) $(OBJS) $(OBJS9)
			$(CC) $(OBJS) $(OBJS9) $(CFLAGS) $(CLIBS) -o $@

$(O_DIR):
			$(MKDIR) $(O_DIR)
$(LIBFT):
			$(MAKE) -C ../libft all

clean:
			$(RM) *.o *.d

fclean:		clean
			$(RM) $(NAME1) $(NAME2)	\
				$(NAME3) $(NAME4)	\
				$(NAME5) $(NAME6)	\
				$(NAME7) $(NAME8)	\
				$(NAME9)

re:			fclean all

-include	$(OBJS:.o=.d)

.PHONY:		all clean fclean re
