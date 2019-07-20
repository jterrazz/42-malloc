/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 14:20:08 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/20 07:40:00 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_block*find_freed_block(size_t size, t_heap **found_heap)
{
    t_heap		*heap;
    t_block		*block;
    t_heap_group	group;

	heap = get_default_heap();
	group = get_heap_group_from_block_size(size);

    while (heap) {
        block = (t_block *)SHIFT_HEAP(heap);
        while (block && heap->group == group) {
            if (block->freed && (block->data_size >= size + sizeof(t_block))) {
                *found_heap = heap;
                return (block);
            }
            block = block->next;
        }
        heap = heap->next;
    }
    return (NULL);
}

static t_block*fill_freed_block(size_t size)
{
    t_block	*freed_block	= NULL;
    t_heap	*freed_heap	= NULL;

    freed_block = find_freed_block(size, &freed_heap);
    if (freed_block && freed_heap) {
        reinit_freed_block(freed_block, size, freed_heap);
        return (freed_block);
    }

    return (NULL);
}

void *ft_malloc(size_t size)
{
    t_heap *heap;
    t_block *block;

    // ft_putstr("Here0\n");

    if (!size)
        return (NULL);
    // if (size < 200)
        // return ft_malloc(size + 1);

    // if (size < 16) // Explain why
    //     return ft_malloc(16); // Bad use 16

    // ft_putstr("Here1\n");
    // log_call(MALLOC);
    // ft_putstr("Here2\n");
    if ((block = fill_freed_block(size)) != NULL) {
        return (SHIFT_BLOCK(block));
    }
    // ft_putstr("Here3\n");

    if (!(heap = get_heap_of_block_size((const size_t)size))) {
        return (NULL);
    }

    void *ret = append_empty_block(heap, size);
    return (ret);
}

void *malloc(size_t size)
{
    // ft_putstr("Start function malloc\n");
	void *ret;

    pthread_mutex_lock(&g_ft_malloc_mutex);
    ret = ft_malloc(size);
    // ft_putstr("Malloc end 1\n");
    if (ret) {
        // ft_putstr("Malloc end 2\n");
        // log_stack(ALLOCATE, (size_t) ret, size);
        // ft_putstr("Malloc end 3\n");
        // if (getenv("MyMallocScribble")) ft_memset(ret, 0xaa, size);
        // ft_putstr("Malloc end 4\n");
    }
    pthread_mutex_unlock(&g_ft_malloc_mutex);
    // ft_putstr("Malloc end 5\n");

    // ft_putstr("End function\n");
    return ret;
}
