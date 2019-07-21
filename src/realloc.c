/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 17:44:52 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/21 10:52:17 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** The realloc() function changes the size of the memory block pointed to
** by ptr to size bytes. The contents will be unchanged in the range from
** the start of the region up to the minimum of the old and new sizes.
*/

void *start_realloc(void *ptr, size_t size)
{
    t_heap	*heap;
    t_block	*block;
    void	*new_ptr;

    if (!ptr)
        return (start_malloc(size));

    heap = get_default_heap();
    search_ptr(&heap, &block, heap, ptr);

    if (!heap || !block)
        return (start_malloc(size));
    else if (size == block->data_size)
        return (ptr);

    new_ptr = start_malloc(size);
    ft_memmove(new_ptr, ptr, block->data_size > size ? size : block->data_size);
    start_free(ptr);

    return (new_ptr);
}

void *realloc(void *ptr, size_t size)
{
    void *res;

    pthread_mutex_lock(&g_ft_malloc_mutex);
    log_detail(REALLOC);
    res = start_realloc(ptr, size);
    pthread_mutex_unlock(&g_ft_malloc_mutex);

    return (res);
}
