# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arupert <arupert@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/23 18:38:49 by arupert           #+#    #+#              #
#    Updated: 2022/07/09 17:26:40 by arupert          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_FILES	= philosophers.c \
			  errors.c \
			  init.c \
			  parser.c \
			  log_messages.c \
			  monitor.c \
			  ft_usleep.c \
			  end.c \
			  lanch.c

OBJS		= $(SRC_FILES:.c=.o)

HEADER		= philosophers.h

NAME		= philo

CC			= cc

CFLAGS		= -Wall -Werror -Wextra -pthread

RM			= rm -f

.PHONY:		all clean fclean re

%.o:		%.c $(HEADER) Makefile
			$(CC) -c $(CFLAGS) $< -o $@

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all:		$(NAME)

clean:
	$(RM) $(OBJS)

fclean:		clean
	$(RM) $(NAME)
	
re:			fclean all
