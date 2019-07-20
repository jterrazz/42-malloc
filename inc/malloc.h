/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 17:50:59 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/20 12:05:32 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
#define MALLOC_H

// medium: getting more memory from the kernel
// learn what is the kernel vs sys
// rename to bucket or heap cell

#define SHIFT_HEAP(start) ((char *)start + sizeof(t_heap))
#define SHIFT_BLOCK(start) ((char *)start + sizeof(t_block))

#define LOGS_PATH "/tmp/malloc.log"

/*
================
0                   512
SMALL     TINY LARGE
*/

#define TINY_HEAP_ALLOCATION_SIZE (4 * getpagesize())
#define TINY_BLOCK_SIZE (TINY_HEAP_ALLOCATION_SIZE / 128)
#define SMALL_HEAP_ALLOCATION_SIZE (16 * getpagesize())
#define SMALL_BLOCK_SIZE (SMALL_HEAP_ALLOCATION_SIZE / 128)
// typically > 512 bytes for large
//renam to max

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h> // rem

//tmp
extern pthread_mutex_t		g_ft_malloc_mutex;

typedef enum e_bool { FALSE, TRUE }				bool;
typedef enum e_bool_bef { B_NULL = 0, B_FALSE, B_TRUE }				bool_bef;
typedef enum e_heap_group { TINY, SMALL, LARGE }	t_heap_group;
typedef enum e_memory_event { ALLOCATE, DEALLOCATE } t_memory_event;
typedef enum e_call_event { MALLOC, CALLOC, FREE, REALLOC, REALLOCF } t_call_event;

typedef enum e_env { ENV_STACK_LOGGING, ENV_FULL_LOGGING, ENV_SCRIBLE } t_env;

/*
** A heap stores data about one mapped zone
*/

// default heap global

typedef struct s_heap {
    struct s_heap	*prev;
    struct s_heap	*next;
    t_heap_group	group;
    size_t		total_size;
    size_t		free_size;
    size_t		block_count;
} t_heap;

/*
** A block stores data for each malloc call
*/

typedef struct s_block {
    struct s_block	*prev;
    struct s_block	*next;
    size_t		data_size;
    bool		freed;
} t_block;

/*
** Library methods
*/

void	*malloc(size_t size);
void	*calloc(size_t count, size_t size);
void    *reallocf(void *ptr, size_t size);
void	*realloc(void *ptr, size_t size);
void	free(void *ptr);
void	show_alloc_mem();
void	show_alloc_meme_ex(void);

/*
** Internal methods
*/

t_heap		*get_default_heap(void);
t_heap		*get_last_heap(t_heap *heap);
t_heap		*get_heap_of_block_size(const size_t size);
void		set_default_heap(t_heap *heap);
t_heap_group	get_heap_group_from_block_size(size_t size);
size_t		get_heap_size_from_block_size(size_t size);
void		print_heap_group(t_heap *heap);

void	*append_empty_block(t_heap *heap, size_t size);
void	reinit_freed_block(t_block *block, size_t size, t_heap *heap);

void convert_ptr(t_heap **found_heap,
    t_block **found_block,
    t_heap *heap,
    void *ptr);

void log_stack(t_memory_event event, size_t arg1, size_t arg2);
void log_call(t_call_event event);

/*
** Utils methods
*/

void	ft_bzero(void *s, size_t n);
void	ft_putstr(char const *s);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	ft_itoa_base(size_t nb, char base, char length, bool prefix);
void    ft_itoa_fd(size_t nb, char base, int fd, bool prefix);
size_t  ft_strlen(const char *s);
void	*ft_memset(void *b, int c, size_t len);
void	ft_putstr_fd(char const *s, int fd);

#endif
