# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/08 16:28:37 by asid-ahm          #+#    #+#              #
#    Updated: 2024/10/05 01:51:25 by asid-ahm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

Name = philo
CC = cc
CFLAGS = -g3
# CFLAGS = -Wall -Wextra -Werror
SRC = 	main.c \
		ft_atoi.c\
		routine.c\
		utils.c\
		check_input.c\
		routine_utils.c
OBJ = $(SRC:.c=.o)

all: $(Name) $(OBJ)
$(Name): $(OBJ)
	$(CC) $(CFLAGS) -o $(Name) $(OBJ) -lpthread
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(Name)
re: fclean all
.PHONY: all clean fclean re