# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/12 13:07:16 by anclarma          #+#    #+#              #
#    Updated: 2021/08/12 05:27:07 by anclarma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
C_FILES		= main.c						\
			  ft_echo.c
SRCS		= $(addprefix srcs/,$(C_FILES))
OBJS		= $(SRCS:.c=.o)
DEPS		= $(OBJS:.o=.d)
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
DEBUG1		= -g3 -fsanitize=leak -fsanitize=undefined -fsanitize=address
DEBUG2		= -g3 -fsanitize=thread
CINCLUDES	= -I ./includes
CLIBS		=

all:		$(NAME)

%.o:%.c
			$(CC) $(CFLAGS) $(CINCLUDES) -MMD -MP -c $< -o $@

$(NAME):	$(OBJS)
			$(CC) $^ $(CFLAGS) $(CLIBS) -o $@

clean:
			rm -f $(OBJS) $(DEPS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

-include	$(DEPS)

.PHONY:		all clean fclean re
