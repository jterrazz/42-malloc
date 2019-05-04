# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/23 18:00:29 by jterrazz          #+#    #+#              #
#    Updated: 2019/05/04 01:59:42 by jterrazz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

# TODO Clean the makefile

# **************************************************************************** #
# FILES             														   #
# **************************************************************************** #

PATH_INC = inc
PATH_LIB = lib
PATH_OBJ = obj
PATH_SRC = src

SOURCES = block.c \
	calloc.c \
	free.c \
	ft_itoa_base.c \
	ft_bzero.c \
	ft_putstr.c \
	ft_memcpy.c \
	ft_memmove.c \
	malloc.c \
	range_default.c \
	range.c \
	realloc.c \
	show_alloc_mem_ex.c \
	show_alloc_mem.c \
	show_range.c \
	size.c

OBJECTS = $(SOURCES:%.c=$(PATH_OBJ)/%.o)

# **************************************************************************** #
# VARIABLES         														   #
# **************************************************************************** #

NAME = libft_malloc_$(HOSTTYPE).so
LIB_NAME = libft_malloc.so

CC = gcc

FLAGS_CC = -Wall -Wextra -Werror
FLAGS_LIB = -shared -fPIC
# Check the reasons for lib flags
# FLAGS_DEBUG = -g -O0

# **************************************************************************** #
# COMMANDS  		    													   #
# **************************************************************************** #

.PHONY: all clean fclean re

all: $(NAME)

# TODO Print logs

$(NAME): $(OBJECTS)
	$(CC) $(FLAGS_LIB) -o $@ $(OBJECTS)
	@rm -f $(LIB_NAME)
	ln -s $(NAME) $(LIB_NAME)
	@echo "Make done"

$(PATH_OBJ)/%.o: $(PATH_SRC)/%.c
	@mkdir -p $(PATH_OBJ)
	$(CC) -fPIC -c -o $@ $(FLAGS_CC) $^ -O0 -g -I $(PATH_INC) # $^ ??

clean:
	@rm -rf $(PATH_OBJ)

fclean: clean
	rm -f $(NAME) $(LIB_NAME)

re: fclean $(NAME)
