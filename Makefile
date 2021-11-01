# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anclarma <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/01 19:28:48 by anclarma          #+#    #+#              #
#    Updated: 2021/11/01 19:32:41 by anclarma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
LIBFT		= libft/libft.a
C_DIR		= srcs
O_DIR		= objs
C_FILES		= main.c					\
			  ft_echo.c					\
			  ft_pwd.c					\
			  ft_exit.c					\
			  ft_env.c					\
			  ft_export.c				\
			  ft_pipe.c					\
			  init_ast.c				\
			  print_ast.c				\
			  clean_ast.c				\
			  utils_ast.c				\
			  utils_tab.c				\
			  exec_ast.c				\
			  init_list.c				\
			  clean_list.c
SRCS		= $(patsubst %, $(C_DIR)/%, $(C_FILES))
O_FILES		= $(C_FILES:.c=.o)
OBJS		= $(patsubst %, $(O_DIR)/%, $(O_FILES))
CC			= gcc
CXX			= g++
CFLAGS		= -Wall -Wextra -Werror		\
			  -MMD -MP
CXXFLAGS	= -Wall -Wextra -Werror		\
			  -std=c++98				\
			  -MMD -MP
LFLAGS		= -Wall -Wextra -Werror
CINCLUDES	= -I ./includes				\
			  -I ./libft/includes
CLIBS		= -L ./libft -lft -lreadline

all:		$(NAME)

check:		all
			@test/run_tests.sh

$(O_DIR)/%.o: $(C_DIR)/%.c
			$(CC) $(CFLAGS) $(CINCLUDES) -c $< -o $@

$(O_DIR)/%.o: $(C_DIR)/%.cpp
			$(CXX) $(CXXFLAGS) $(CINCLUDES) -c $< -o $@

$(O_DIR):
			mkdir $(O_DIR)

$(NAME):	$(LIBFT) $(O_DIR) $(OBJS)
			$(CC) $(OBJS) $(LFLAGS) $(CLIBS) -o $@

$(LIBFT):
			make -C libft all

clean:
			make -C libft fclean
			make -C test fclean
			rm -rf $(O_DIR)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

-include	$(OBJS:.o=.d)

.PHONY:		all check clean fclean re
