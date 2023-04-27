# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mochaoui <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/21 23:34:36 by mochaoui          #+#    #+#              #
#    Updated: 2023/04/26 10:54:34 by mochaoui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGGS = -Werror -Wall -Wextra

OBJS = ${SRCS:.c=.o}

RM = rm -rf

SRCS = main.c

$(NAME) :
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

all : $(NAME)

fclean : clean
	${RM} ${NAME}
clean :
	${RM} ${OBJS}

re : fclean all

