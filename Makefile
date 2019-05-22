# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/23 18:00:29 by jterrazz          #+#    #+#              #
#    Updated: 2019/05/22 21:17:55 by jterrazz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

# **************************************************************************** #
# FILES             														   #
# **************************************************************************** #

PATH_INC = inc
PATH_LIB = lib
PATH_OBJ = obj
PATH_SRC = src

SOURCES += block.c range_default.c range.c size.c
SOURCES += print/show_alloc_mem_ex.c print/show_alloc_mem.c print/show_range.c
SOURCES += utils/ft_itoa_base.c utils/ft_bzero.c utils/ft_putstr.c \
	utils/ft_memcpy.c utils/ft_memmove.c
SOURCES += calloc.c free.c malloc.c realloc.c

OBJECTS = $(SOURCES:%.c=$(PATH_OBJ)/%.o)

# **************************************************************************** #
# VARIABLES         														   #
# **************************************************************************** #

NAME = libft_malloc_$(HOSTTYPE).so
LIB_NAME = libft_malloc.so

CC = gcc

FLAGS_CC = -Wall -Wextra -Werror
FLAGS_LIB = -shared -fPIC

# **************************************************************************** #
# COMMANDS  		    													   #
# **************************************************************************** #

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(FLAGS_LIB) -o $@ $(OBJECTS)
	@rm -f $(LIB_NAME)
	ln -s $(NAME) $(LIB_NAME)
	@echo "Make done"

$(PATH_OBJ)/%.o: $(PATH_SRC)/%.c
	@mkdir -p $(@D)
	$(CC) -fPIC -c -o $@ $(FLAGS_CC) $^ -O0 -g -I $(PATH_INC)

clean:
	@rm -rf $(PATH_OBJ)

fclean: clean
	rm -f $(NAME) $(LIB_NAME)

re: fclean $(NAME)
