/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 14:20:08 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/20 15:24:27 by jterrazz         ###   ########.fr       */
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
            int temp = block->freed;
            int temp2 = (block->data_size >= size + sizeof(t_block));

            if (temp && temp2) {
                *found_heap = heap;

                // ft_putstr("Will replace an empty block of "); //tmp
                // ft_itoa_base(block->data_size, 10, 0, FALSE);
                // ft_putstr(" by a bloc of size "); //tmp
                // ft_itoa_base(size, 10, 0, FALSE);
                // ft_putstr(" (plus X pf bloc size "); //tmp
                // ft_itoa_base(sizeof(t_block), 10, 0, FALSE);
                // ft_putstr(" )"); //tmp
                // ft_putstr("\n"); //tmp

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

void *start_malloc(size_t size)
{
    t_heap *heap;
    t_block *block;

    // ft_putstr("m0");
    if (!size)
        return (NULL);
    size = (size + 15) & ~15; //tmp // Should print this size print in show_mem_alloc ? //Put in medium and macro for the calcccc of modulo :))))))))

    log_call(MALLOC);
    // ft_putstr("m1");
    if ((block = fill_freed_block(size)) != NULL) {
        // ft_putstr("M2");
        return (SHIFT_BLOCK(block));
    }

    // ft_putstr("m2");
    if (!(heap = get_heap_of_block_size((const size_t)size))) {
        return (NULL);
    }

    // ft_putstr("m3");
    void *ret = append_empty_block(heap, size);
    // ft_putstr("m4");
    return (ret);
}

// Put in debug bonus
void *malloc(size_t size)
{
	void *ret;

    // ft_putstr("Malloc\n");
    // show_alloc_mem();
    pthread_mutex_lock(&g_ft_malloc_mutex);
    ret = start_malloc(size);
    if (ret) {
        log_stack(ALLOCATE, (size_t) ret, size);
        // if (getenv("MyMallocScribble")) ft_memset(ret, 0xaa, size);
    }
    pthread_mutex_unlock(&g_ft_malloc_mutex);
    return ret;
}
