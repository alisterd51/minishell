# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/12 13:07:16 by anclarma          #+#    #+#              #
#    Updated: 2021/08/12 17:48:15 by anclarma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a
C_FILES		= ft_strlen.c
SRCS		= $(addprefix srcs/,$(C_FILES))
OBJS		= $(SRCS:.c=.o)
DEPS		= $(OBJS:.o=.d)
CC			= cc
AR			= ar rc
CFLAGS		= -Wall -Wextra -Werror
CINCLUDES	=
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
