# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/09 07:43:30 by fraalexa          #+#    #+#              #
#    Updated: 2026/02/09 14:23:47 by fraalexa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
FLAGS = -Wall -Wextra -Werror -g
INC_DIR = ./include
SRC_DIR = ./src
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:.c=.o)

%.o : %.c
	$(CC) $(FLAGS) -I$(INC_DIR) -c $< -o $@

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

all : $(NAME)

clean : 
	rm -f $(OBJ) 

fclean : clean
	rm -f $(NAME)

re : fclean all

