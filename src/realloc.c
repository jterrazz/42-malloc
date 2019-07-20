/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 17:44:52 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/20 22:59:10 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void*realloc(void *ptr, size_t size)
{
    t_heap	*heap;
    t_block	*block;
    void	*new_ptr;
    size_t	data_size;

    // show_alloc_mem();
    pthread_mutex_lock(&g_ft_malloc_mutex);
    // ft_putstr("Realloc/n");

    log_call(REALLOC);
    if (!ptr) {
        pthread_mutex_unlock(&g_ft_malloc_mutex);
        // ft_putstr("No ptr realloc/n");
        return (malloc(size));
    }
    // if (!size) {
    //     size = 50; // del
    // }

    // ft_putstr("Hello/n");
    heap = get_default_heap();
    convert_ptr(&heap, &block, heap, ptr);
    // ft_putstr("Hello2/n");
    if (!heap || !block) {
        pthread_mutex_unlock(&g_ft_malloc_mutex);
        // ft_putstr("Realloc byebye/n");
        return (malloc(size));
    }

    // ft_putstr("Oh con/n");
    if (size == block->data_size) {
        pthread_mutex_unlock(&g_ft_malloc_mutex);
        // ft_putstr("Realloc la bise/n");
        return (ptr);
    }

    // ft_putstr("Oh gros/n");
    data_size = block->data_size > size ? size : block->data_size;
    // ft_putstr("ISSS/nc");

    pthread_mutex_unlock(&g_ft_malloc_mutex);
    new_ptr = malloc(size);

    pthread_mutex_lock(&g_ft_malloc_mutex); //tmp
    ft_memmove(new_ptr, ptr, data_size);
    pthread_mutex_unlock(&g_ft_malloc_mutex); //tmp

    free(ptr);

    return (new_ptr);
}
