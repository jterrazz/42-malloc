/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 14:20:08 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/21 10:05:45 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/* Explain malloc here */

void *start_malloc(size_t size)
{
    t_heap *heap;
    t_block *block;

    log_call(MALLOC);

    if (!size)
        return (NULL);
    size = (size + 15) & ~15; // Should print this size print in show_mem_alloc ? //Put in medium and macro for the calcccc of modulo :))))))))

    if ((block = fill_freed_block(size)))
        return (SHIFT_BLOCK(block));
    if (!(heap = get_heap_of_block_size((const size_t)size)))
        return (NULL);

    return (append_empty_block(heap, size));
}

// Put in debug bonus
void *malloc(size_t size)
{
	void *res;

    pthread_mutex_lock(&g_ft_malloc_mutex);
    if ((res = start_malloc(size))) {
        log_stack(ALLOCATE, (size_t) res, size); // Use modulo here if applicate
        if (getenv_cached(ENV_SCRIBBLE)) ft_memset(res, 0xaa, size);
    }
    pthread_mutex_unlock(&g_ft_malloc_mutex);

    return (res);
}
