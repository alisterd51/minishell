# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anclarma <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/01 19:28:48 by anclarma          #+#    #+#              #
#    Updated: 2022/01/19 02:10:04 by anclarma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
LIBFT		= libft/libft.a
C_DIR		= srcs
O_DIR		= objs
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
			  utils_tab.c				\
			  utils_tab2.c				\
			  utils_list.c				\
			  exec_ast.c				\
			  exec_redir.c				\
			  ft_pipe.c					\
			  init_list.c				\
			  clean_list.c				\
			  solve_path.c				\
			  ret_status.c				\
			  end_status.c				\
			  colector.c
SRCS		= $(patsubst %, $(C_DIR)/%, $(C_FILES))
O_FILES		= $(C_FILES:.c=.o)
OBJS		= $(patsubst %, $(O_DIR)/%, $(O_FILES))
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror		\
			  -Wconversion				\
			  -Wpedantic				\
			  -pedantic-errors			\
			  -std=c99					\
			  -MMD -MP					\
			  -D_POSIX_C_SOURCE	-g3#	\
			  -D_XOPEN_SOURCE			\
			  -D_XOPEN_SOURCE_EXTENDED
LFLAGS		= -Wall -Wextra -Werror
CINCLUDES	= -I ./includes				\
			  -I ./libft/includes
CLIBS		= -L ./libft -lft -lreadline

all:		$(NAME)

debug:		CFLAGS += -fsanitize=address	\
				-fsanitize=undefined		\
				-fsanitize=leak				\
				-g3
debug:		LFLAGS += -fsanitize=address	\
				-fsanitize=undefined		\
				-fsanitize=leak				\
				-g3
debug:		$(NAME)

check:		all
			@test/run_tests.sh

$(O_DIR)/%.o: $(C_DIR)/%.c
			$(CC) $(CFLAGS) $(CINCLUDES) -c $< -o $@

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

.PHONY:		all debug check clean fclean re
