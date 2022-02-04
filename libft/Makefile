# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anclarma <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/01 20:14:19 by anclarma          #+#    #+#              #
#    Updated: 2022/02/04 20:39:36 by anclarma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a
C_DIR		= srcs
O_DIR		= objs
C_FILES		= ft_lstadd_back.c			\
			  ft_lstadd_front.c			\
			  ft_lstclear.c				\
			  ft_lstdelone.c			\
			  ft_lstiter.c				\
			  ft_lstlast.c				\
			  ft_lstmap.c				\
			  ft_lstnew.c				\
			  ft_lstsize.c				\
			  ft_isalnum.c				\
			  ft_isalpha.c				\
			  ft_isascii.c				\
			  ft_isdigit.c				\
			  ft_isprint.c				\
			  ft_isspace.c				\
			  ft_tolower.c				\
			  ft_toupper.c				\
			  ft_memccpy.c				\
			  ft_memcpy.c				\
			  ft_memchr.c				\
			  ft_memcmp.c				\
			  ft_memmove.c				\
			  ft_memset.c				\
			  ft_putchar_fd.c			\
			  ft_putendl_fd.c			\
			  ft_putnbr_fd.c			\
			  ft_putstr_fd.c			\
			  ft_strchr.c				\
			  ft_strrchr.c				\
			  ft_strcmp.c				\
			  ft_strncmp.c				\
			  ft_strdup.c				\
			  ft_strndup.c				\
			  ft_strjoin.c				\
			  ft_strlcat.c				\
			  ft_strlcpy.c				\
			  ft_strlen.c				\
			  ft_strnlen.c				\
			  ft_strnstr.c				\
			  ft_bzero.c				\
			  ft_atoi.c					\
			  ft_itoa.c					\
			  ft_calloc.c				\
			  ft_realloc.c				\
			  ft_realpath.c				\
			  get_next_line.c
SRCS		= $(patsubst %, $(C_DIR)/%, $(C_FILES))
O_FILES		= $(C_FILES:.c=.o)
OBJS		= $(patsubst %, $(O_DIR)/%, $(O_FILES))
CC			= clang
CXX			= g++
AR			= ar rc
CFLAGS		= -Wall -Wextra -Werror		\
			  -MMD -MP -g3
CXXFLAGS	= -Wall -Wextra -Werror		\
			  -std=c++98				\
			  -MMD -MP
LFLAGS		= -Wall -Wextra -Werror
CINCLUDES	= -I ./includes
CLIBS		=

all:		$(NAME)

check:		all

$(O_DIR)/%.o: $(C_DIR)/%.c
			$(CC) $(CFLAGS) $(CINCLUDES) -c $< -o $@

$(O_DIR)/%.o: $(C_DIR)/%.cpp
			$(CXX) $(CXXFLAGS) $(CINCLUDES) -c $< -o $@

$(O_DIR):
			mkdir $(O_DIR)

$(NAME):	$(O_DIR) $(OBJS)
			$(AR) $@ $(OBJS)

clean:
			rm -rf $(O_DIR)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

-include	$(OBJS:.o=.d)

.PHONY:		all clean fclean re
