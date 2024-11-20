# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahamuyel <ahamuyel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/10 14:38:26 by ahamuyel          #+#    #+#              #
#    Updated: 2024/11/20 12:41:24 by ahamuyel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc 
CFLAGS = -Wall -Wextra -Werror



SRCS = 	main.c \
		initialization.c

OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
	