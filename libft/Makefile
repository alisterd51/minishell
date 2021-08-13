# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/12 13:07:16 by anclarma          #+#    #+#              #
#    Updated: 2021/08/13 04:48:05 by anclarma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a
C_FILES		= ft_isalnum.c				\
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
			  ft_strlen.c
SRCS		= $(addprefix srcs/,$(C_FILES))
OBJS		= $(SRCS:.c=.o)
DEPS		= $(OBJS:.o=.d)
CC			= cc
AR			= ar rc
CFLAGS		= -Wall -Wextra -Werror
CINCLUDES	= -I ./includes
CLIBS		=

all:		$(NAME)

%.o:%.c
			$(CC) $(CFLAGS) $(CINCLUDES) -MMD -MP -c $< -o $@

$(NAME):	$(OBJS)
			$(AR) $@ $^


clean:
			rm -f $(OBJS) $(DEPS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

-include	$(DEPS)

.PHONY:		all clean fclean re
