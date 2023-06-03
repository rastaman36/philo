# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mochaoui <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/21 23:34:36 by mochaoui          #+#    #+#              #
#    Updated: 2023/06/02 23:31:55 by mochaoui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

#CC = cc

CFLAGGS = -Werror -Wall -Wextra -fsanitize=address -g3

OBJS = ${SRCS:.c=.o}

RM = rm -rf

SRCS = main.c init_data.c utls.c

$(NAME) :
	cc -Werror -Wall -Wextra -fsanitize=address -g3 $(SRCS) -o $(NAME)

all : $(NAME)

fclean : clean
	${RM} ${NAME}
clean :
	${RM} ${OBJS}

re : fclean all

