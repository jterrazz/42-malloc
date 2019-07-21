/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 23:47:26 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/21 09:38:55 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
// Add description on top of main functions + add this in the todo file

// Is never at the end, always between
static  void fill_free_block(t_block *block, size_t size, t_heap *heap) {
	t_block *free_block = SHIFT_BLOCK(block) + size;

	init_block(free_block, block->next - free_block);
	free_block->freed = TRUE;
	free_block->prev = block;
	free_block->next = block->next;
	heap->block_count++;
	block->next = free_block;
	block->data_size = size;
	block->freed = FALSE;
}

static t_block*find_free_block(size_t size, t_heap **found_heap)
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
    t_block	*block	= NULL;
    t_heap	*heap	= NULL;

    block = find_free_block(size, &heap);
    if (block && heap) {
        fill_free_block(block, size, heap);
        return (block);
    }

    return (NULL);
}
