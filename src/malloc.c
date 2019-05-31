/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 14:20:08 by jterrazz          #+#    #+#             */
/*   Updated: 2019/05/31 20:42:10 by jterrazz         ###   ########.fr       */
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

void*malloc(size_t size)
{
	t_heap *heap;
    t_block *block;

    if (!size)
        return (NULL);

    if ((block = fill_freed_block(size)) != NULL)
        return (SHIFT_BLOCK(block));

    if (!(heap = get_heap_of_block_size((const size_t)size)))
        return (NULL);

    return (append_empty_block(heap, size));
}
