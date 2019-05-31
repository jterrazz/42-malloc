# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/23 18:00:29 by jterrazz          #+#    #+#              #
#    Updated: 2019/05/31 20:10:27 by jterrazz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# FILES             														   #
# **************************************************************************** #

INC_PATH = ../inc
LIB_PATH = ..
BUILD_PATH = obj
SRC_PATH = src

SOURCES = main.c test_malloc.c test_realloc.c test_mixed.c print.c test_limit.c
LIB_SOURCES = -L.. -lft_malloc

OBJECTS = $(SOURCES:%.c=$(BUILD_PATH)/%.o)

# **************************************************************************** #
# VARIABLES         														   #
# **************************************************************************** #

NAME = test

CC = gcc

FLAGS_CC = # -Wall -Wextra -Werror

# **************************************************************************** #
# COMMANDS  		    													   #
# **************************************************************************** #

.PHONY: all clean fclean re test

all: $(NAME)

$(NAME): $(OBJECTS)
	@make -C $(LIB_PATH)
	$(CC) $(FLAGS_CC) -o $@ $^ $(LIB_SOURCES)
	@echo "Compilation successful"

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS_CC) -c -o $@ $< -I $(INC_PATH)

clean:
	@make clean -C $(LIB_PATH)
	@rm -rf $(BUILD_PATH)
	@echo "Clean \033[33mok\033[0m"

fclean: clean
	@make fclean -C $(LIB_PATH)
	@rm -f $(NAME) $(LIB_NAME)
	@echo "Fclean \033[33mok\033[0m"

re: fclean $(NAME)
