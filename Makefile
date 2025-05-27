# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isegura- <isegura-@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/16 09:29:49 by isegura-          #+#    #+#              #
#    Updated: 2025/05/27 09:57:48 by isegura-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -MMD -Wall -Wextra -Werror -fsanitize=thread #-fsanitize=thread
SRC_DIR = ./src
OBJ_DIR = ./obj
INC_DIR = ./inc


SRC = 	$(SRC_DIR)/init.c \
		$(SRC_DIR)/main.c \
		$(SRC_DIR)/mutex.c \
		$(SRC_DIR)/parsing.c \
		$(SRC_DIR)/print.c \
		$(SRC_DIR)/routine.c \
		$(SRC_DIR)/utils.c

OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

DEPS = $(OBJ:%.o=%.d)

INCLUDE = $(INC_DIR)/philo.h

all: $(NAME)

$(NAME): 	$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE) Makefile
				mkdir -p $(OBJ_DIR)
				$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -rf $(OBJ_DIR)

fclean: clean
		rm -f $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re bonus
