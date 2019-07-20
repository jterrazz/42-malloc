/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 23:47:26 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/20 23:59:52 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
// Add description on top of main functions + add this in the todo file

// goto static
void reinit_freed_block(t_block *block, size_t size, t_heap *heap) {
	t_block *freed_block = (t_block *) (SHIFT_BLOCK(block) + size);

	init_block(freed_block, block->data_size - size - sizeof(t_block));
	freed_block->freed = TRUE;
	block->freed = FALSE;
	block->data_size = size;
	freed_block->prev = block;
	freed_block->next = block->next;
	block->next = freed_block;
	heap->block_count++;
	heap->free_size -= size;
}

static t_block*find_freed_block(size_t size, t_heap **found_heap)
{
    t_heap		*heap;
    t_block		*block;
    t_heap_group	group;

	heap = get_default_heap();
	group = get_heap_group_from_block_size(size);

    while (heap) {
        block = (t_block *)SHIFT_HEAP(heap);

        while (heap->group == group && block) {
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

  t_block*fill_freed_block(size_t size)
{
    t_block	*fillable	= NULL;
    t_heap	*freed_heap	= NULL;

    fillable = find_freed_block(size, &freed_heap);
    if (fillable && freed_heap) {
        reinit_freed_block(fillable, size, freed_heap);
        return (fillable);
    }

    return (NULL);
}
