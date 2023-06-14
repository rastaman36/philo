# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mochaoui <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/21 23:34:36 by mochaoui          #+#    #+#              #
#    Updated: 2023/06/14 11:56:02 by mochaoui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
FLAGS = -Wall -Wextra -Werror -pthread -fsanitize=thread

SRCS =	main.c				\
		init_data.c			\
		utls.c 				\
		sonar.c 			\
		valide_args.c		\
		
all : $(NAME)

$(NAME) : $(SRCS)
	@gcc $(FLAGS) $(SRCS) -o $(NAME)

clean :
	@rm -rf $(NAME)
fclean :
	@rm -rf $(NAME)

re: fclean all
