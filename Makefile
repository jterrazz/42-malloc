# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/23 18:00:29 by jterrazz          #+#    #+#              #
#    Updated: 2019/07/20 10:12:06 by jterrazz         ###   ########.fr        #
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

SOURCES += block.c heap_default.c heap.c size.c global.c
SOURCES += log/show_alloc_mem_ex.c log/show_alloc_mem.c log/show_heap.c \
	log/logs.c
SOURCES += libc/ft_itoa_base.c libc/ft_bzero.c libc/ft_putstr.c \
	libc/ft_memcpy.c libc/ft_memmove.c libc/ft_memset.c
SOURCES += calloc.c free.c malloc.c realloc.c

OBJECTS = $(SOURCES:%.c=$(PATH_OBJ)/%.o)

# **************************************************************************** #
# VARIABLES         														   #
# **************************************************************************** #

NAME = libft_malloc_$(HOSTTYPE).so
LIB_NAME = libft_malloc.so

CC = gcc

FLAGS_CC = -Wall -Wextra -Werror
FLAGS_LIB = -shared

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
	$(CC) -fPIC -c -o $@ $(FLAGS_CC) $^ -O0 -g -I $(PATH_INC) # find why fpic

clean:
	@rm -rf $(PATH_OBJ)
	@echo "Clean done"

fclean: clean
	@rm -f $(NAME) $(LIB_NAME)
	@echo "Fclean done"

re: fclean $(NAME)
