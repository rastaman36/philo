# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mochaoui <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/21 23:34:36 by mochaoui          #+#    #+#              #
#    Updated: 2023/06/01 15:19:49 by mochaoui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGGS = -Werror -Wall -Wextra -fsanitize=address

OBJS = ${SRCS:.c=.o}

RM = rm -rf

SRCS = main.c init_data.c utls.c

$(NAME) :
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

all : $(NAME)

fclean : clean
	${RM} ${NAME}
clean :
	${RM} ${OBJS}

re : fclean all

