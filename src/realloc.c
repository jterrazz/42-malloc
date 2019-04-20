/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 17:44:52 by jterrazz          #+#    #+#             */
/*   Updated: 2019/04/20 20:37:38 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static size_t get_space_around_with_start(t_range *range, t_block *block, t_block **start) {
    size_t total_size = block->data_size;
    t_block *block_save = block;

    while(block->prev && block->prev->freed) {
        block = block->prev;
        total_size += block->data_size + sizeof(t_block);
    }
    *start = block;
    block = block_save;
    while(block->next && block->next->freed) {
        block = block->next;
        total_size += block->data_size + sizeof(t_block);
    }
    // If at end, add free space
    if (!block->next)
        total_size += range->free_size;
    return total_size;
}

static t_block *realloc_in_freed_block(t_range *range, t_block *block, t_block *start, size_t size) {
    if (range->block_count == 1) {
        start->data_size = size;
        range->free_size -= block->data_size - size;
        return block;
    }
    // TODO Problem if 1st is freed and 2nd is realloc ? => cause free will
    free(SHIFT_BLOCK(block));
    // ft_memmove(SHIFT_BLOCK(start), SHIFT_BLOCK(block), size);
    reinit_freed_block(start, size, range);
    return start;
}

void *realloc(void *ptr, size_t size) { // Illustrate a realloc with 2 freed objects around
    t_range *range = get_default_range();
    t_block *block = NULL;
    t_block *start = NULL;

    convert_ptr(&range, &block, range, ptr);
    if (size == block->data_size)
        return ptr;
    size_t available_space_around = get_space_around_with_start(range, block, &start); // TODO Check doesnt break with LARGE
    // If need a new block
    if (size + sizeof(t_block) > available_space_around) {
        printf("Need to re malloc\n");
        ptr = malloc(size);
        // ft_memmove(ptr, SHIFT_BLOCK(block), size);
        free(SHIFT_BLOCK(block));
    } else if (size + sizeof(t_block) < available_space_around) { // Check and explain in the README why we sometimes don't reallocate with a different size
        printf("Realloc with an existing block\n");
    // memmove
    // reange the blocks without loosing data
        ptr = SHIFT_BLOCK(realloc_in_freed_block(range, block, start, size));
    }

    return ptr;

    // TODO Make a test for the overlapping realloc in both sides

	// Case where it's stricly smaller
    // If smaller but no place for block (like with size-1) go for a new one (but check the freed zones next to it);
	// Case where it's bigger and can expand to free spaces
	// Case where it needs to malloc, memcpy and then unmap the old mapped zone
    //

	// Will probably change the type too
	// Need to unmap if no more
}
