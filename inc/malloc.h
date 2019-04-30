/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 17:50:59 by jterrazz          #+#    #+#             */
/*   Updated: 2019/04/30 17:58:33 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
#define MALLOC_H

#define SHIFT_RANGE(start) ((char *)start + sizeof(t_range)) // +1 ?
#define SHIFT_BLOCK(start) ((char *)start + sizeof(t_block)) // +1 ?
// Verify that adding to one mapped has space for the struct

#define TINY_BLOCK_SIZE 128
#define TINY_RANGE_ALLOCATION_SIZE (2 * getpagesize())

#define SMALL_BLOCK_SIZE 1024
#define SMALL_RANGE_ALLOCATION_SIZE (16 * getpagesize())

#include <stdio.h> // Maybe delete ?
#include <unistd.h> // Maybe delete ?
#include <stdlib.h> // Maybe delete ?
#include <sys/mman.h> // Maybe delete ?
// TODO Only add the required functions // TODO Use my libs

typedef enum { FALSE, TRUE } bool;

typedef enum e_range_group { TINY, SMALL, LARGE } t_range_group;

/*
** A range represents one mapped memory zone
*/

typedef struct s_range {
	struct s_range *prev; // Delete ?
	struct s_range *next;
	t_range_group group;
	size_t total_size; // Maybe delete
	size_t free_size; // Maybe delete // overflow case
	size_t block_count;
} t_range;

/*
** A block stores the metadata for one malloc
*/

typedef struct s_block {
	struct s_block *prev; // Delete ?
	struct s_block *next;
	size_t data_size;
	bool freed;
} t_block;

/*
** Malloc library functions
*/

// Check prototypes are identical
void            *malloc(size_t size);
void            *calloc(size_t count, size_t size);
void            *realloc(void *ptr, size_t size);
void            free(void *ptr);
void            show_alloc_mem();
void            show_alloc_meme_ex(void);

/*
** Static variables getters and setters
*/

t_range         *get_default_range(void);
void            set_default_range(t_range *range);

/*
** Internal functions
*/

void			ft_bzero(void *s, size_t n);
void            ft_putstr(char const *s);
void            *ft_memmove(void *dst, const void *src, size_t len);
void            *ft_memcpy(void *dst, const void *src, size_t n);
void            ft_itoa_base(size_t nb, char base, char length);

void            reinit_freed_block(t_block *block, size_t size, t_range *range);
void            print_range_group(t_range *range);
void            convert_ptr(t_range **found_range, t_block **found_block,
                            t_range *range, void *ptr);
void            init_empty_block(t_block *block, size_t size);
void            *append_empty_block(t_range *range, size_t size);
t_range         *get_range_of_block_size(const size_t size);
t_range_group   get_range_group_from_block_size(size_t size);
size_t          get_range_allocation_from_block_size(size_t size);

#endif
