/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 17:44:52 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/20 15:20:42 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void*realloc(void *ptr, size_t size)
{
    t_heap	*heap;
    t_block	*block;
    void	*new_ptr;
    size_t	data_size;

    // ft_putstr("Realloc/n");
    // show_alloc_mem();
    pthread_mutex_lock(&g_ft_malloc_mutex);

    log_call(REALLOC);
    if (!ptr) {
        pthread_mutex_unlock(&g_ft_malloc_mutex);
        return (malloc(size));
    }
    if (!size) {
        pthread_mutex_unlock(&g_ft_malloc_mutex);
        return (ptr);
    }

    heap = get_default_heap();
    convert_ptr(&heap, &block, heap, ptr);
    if (!heap || !block) {
        pthread_mutex_unlock(&g_ft_malloc_mutex);
        return (malloc(size));
    }

    if (size == block->data_size) {
        pthread_mutex_unlock(&g_ft_malloc_mutex);
        return (ptr);
    }

    data_size = block->data_size > size ? size : block->data_size;

    pthread_mutex_unlock(&g_ft_malloc_mutex);
    new_ptr = malloc(size);
    ft_memmove(new_ptr, ptr, data_size);
    free(ptr);

    return (new_ptr);
}
