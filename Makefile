# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lzaccome <lzaccome@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/01 19:28:48 by anclarma          #+#    #+#              #
#    Updated: 2022/02/06 00:24:00 by lzaccome         ###   ########.fr        #
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
			  token_to_ast.c			\
			  print_ast.c				\
			  clean_ast.c				\
			  utils_ast.c				\
			  utils_builtin.c			\
			  utils_tab.c				\
			  utils_tab2.c				\
			  utils_list.c				\
			  utils_heredoc.c			\
			  exec_ast.c				\
			  exec_builtin.c			\
			  exec_redir.c				\
			  ft_heredoc.c				\
			  ft_handler.c				\
			  ft_pipe.c					\
			  init_list.c				\
			  init_command.c			\
			  clean_list.c				\
			  solve_path.c				\
			  ret_status.c				\
			  end_status.c				\
			  colector.c				\
			  lzac_pars1.c				\
			  lzac_pars2.c				\
			  expend.c					\
			  pars_list.c				\
			  get_type.c				\
			  pars_error.c				\
			  ft_pars_pipe.c			\
			  ft_pars_type.c
SRCS		= $(patsubst %, $(C_DIR)/%, $(C_FILES))
O_FILES		= $(C_FILES:.c=.o)
OBJS		= $(patsubst %, $(O_DIR)/%, $(O_FILES))
CC			= clang
CFLAGS		= -Wall -Wextra -Werror		\
			  -MMD -MP -g3
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

check:		fclean all
			@test/run_tests.sh

$(O_DIR)/%.o: $(C_DIR)/%.c
			$(CC) $(CFLAGS) $(CINCLUDES) -c $< -o $@

$(O_DIR):
			mkdir $(O_DIR)

$(NAME):	$(LIBFT) $(O_DIR) $(OBJS)
			$(CC) $(OBJS) $(LFLAGS) $(CLIBS) -o $@

malloc_test: $(LIBFT) $(O_DIR) $(OBJS)
	$(CC) $(LFLAGS) -fsanitize=undefined -rdynamic -o $@ ${OBJS} $(CLIBS) -L. -lmallocator

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
