/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 14:20:08 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/21 15:06:05 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** The malloc() function allocates size bytes and returns a pointer to the
** allocated memory. The memory is not initialized. If size is 0, then malloc()
** returns either NULL, or a unique pointer value that can later be successfully
** passed to free().

** Memory allocations are 16-byte aligned, as exepected on MacOS (with vim for example)
*/

void *start_malloc(size_t size)
{
    t_heap *heap;
    t_block *block;
    void *res;

    if (!size)
        return (NULL);
    size = (size + 15) & ~15;

    if ((block = try_filling_available_block(size)))
        return (BLOCK_SHIFT(block));
    if (!(heap = get_heap_of_block_size((const size_t)size)))
        return (NULL);

    res = append_empty_block(heap, size);
    log_stack(ALLOCATE, size);
    return (res);
}

void *malloc(size_t size)
{
	void *res;

    pthread_mutex_lock(&g_ft_malloc_mutex);
    log_detail(MALLOC);
    if ((res = start_malloc(size))) {
        if (getenv_cached(ENV_SCRIBBLE)) ft_memset(res, 0xaa, size);
    }
    pthread_mutex_unlock(&g_ft_malloc_mutex);

    return (res);
}
