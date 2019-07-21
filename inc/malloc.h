/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 17:50:59 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/21 15:33:40 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
#define MALLOC_H

#define HEAP_SHIFT(start) ((void *)start + sizeof(t_heap))
#define BLOCK_SHIFT(start) ((void *)start + sizeof(t_block))

#define LOGS_PATH "/tmp/malloc.log"

/*
** For a pagesize of 4096 bytes
**
** TINY  - block < 128 bytes  - heap 16 KB
** SMALL - block < 1024 bytes - heap 128 KB
** LARGE - block > 1024 bytes
*/

#define TINY_HEAP_ALLOCATION_SIZE (4 * getpagesize())
#define TINY_BLOCK_SIZE (TINY_HEAP_ALLOCATION_SIZE / 128)
#define SMALL_HEAP_ALLOCATION_SIZE (32 * getpagesize())
#define SMALL_BLOCK_SIZE (SMALL_HEAP_ALLOCATION_SIZE / 128)

#include <fcntl.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <unistd.h>

typedef enum e_bool { FALSE,
                        TRUE }
                                                        t_bool;
typedef enum e_heap_group { TINY, SMALL,
                            LARGE }
                                                        t_heap_group;
typedef enum e_stack_event { ALLOCATE,
                             DEALLOCATE }
                                                        t_stack_event;
typedef enum e_detail_event { MALLOC, CALLOC, FREE, REALLOC, REALLOCF,
                              HEAP_CREATE,
                              HEAP_DELETE }
                                                        t_detail_event;
typedef enum e_env { ENV_STACK_LOGGING	= 1 << 0, ENV_FULL_LOGGING = 1 << 1,
                     ENV_SCRIBBLE	= 1 << 2 }	t_env;

/*
** A heap stores data about one mapped zone
*/

typedef struct s_heap {
    struct s_heap	*prev;
    struct s_heap	*next;
    t_heap_group	group;
    size_t		total_size;
    size_t		free_size;
    size_t		block_count;
} t_heap;

extern pthread_mutex_t	g_ft_malloc_mutex;
extern t_heap		*g_heap_anchor;

/*
** A block stores data for each malloc call
*/

typedef struct s_block {
    struct s_block	*prev;
    struct s_block	*next;
    size_t		data_size;
    t_bool		freed;
} t_block;

/*
** Library methods
*/

void	*malloc(size_t size);
void	*calloc(size_t count, size_t size);
void	*realloc(void *ptr, size_t size);
void	*reallocf(void *ptr, size_t size);
void	free(void *ptr);
void	show_alloc_mem();
void	show_alloc_mem_hex(void);

/*
** Internal methods
*/

void find_available_block(size_t size,
    t_heap **res_heap,
    t_block **res_block);
t_block		*get_last_block(t_block *block);
void		*start_malloc(size_t size);
void		start_free(void *ptr);
void		*start_realloc(void *ptr, size_t size);
t_heap		*get_last_heap(t_heap *heap);
t_heap		*get_heap_of_block_size(const size_t size);
t_heap_group	get_heap_group_from_block_size(size_t size);
size_t		get_heap_size_from_block_size(size_t size);
void		print_heap_group(t_heap *heap);

void	*append_empty_block(t_heap *heap, size_t size);
void	reinit_freed_block(t_block *block, size_t size, t_heap *heap);
void	setup_block(t_block *block, size_t size);
void	delete_heap_if_empty(t_heap *heap);

t_block *merge_block(t_heap *heap, t_block *block);
t_heap	*create_heap(t_heap_group group, size_t block_size);

void remove_block_if_last(t_heap *heap, t_block *block);

void search_ptr(t_heap **found_heap,
    t_block **found_block,
    t_heap *heap,
    void *ptr);

void	log_stack(t_stack_event event, size_t size);
void	log_detail(t_detail_event event);
t_block *try_filling_available_block(size_t size);
t_bool	getenv_cached(t_env env);

void debug_heap_block();        //tmp

/*
** Utils methods
*/

void	ft_bzero(void *s, size_t n);
void	ft_putstr(char const *s);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	ft_itoa_base(size_t nb, char base, char length, t_bool prefix);
void	ft_itoa_fd(size_t nb, char base, int fd, t_bool prefix);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *b, int c, size_t len);
void	ft_putstr_fd(char const *s, int fd);
void	ft_putchar_fd(char c, int fd);

#endif
