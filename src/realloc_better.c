/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_better.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 17:44:52 by jterrazz          #+#    #+#             */
/*   Updated: 2019/04/25 16:03:12 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static size_t get_space_around_with_start(t_range *range, t_block *block,
                                          t_block **start) {
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

static t_block *realloc_in_freed_block(t_range *range, t_block *block,
                                       t_block *start, size_t size) {
	if (range->block_count == 1) { // Verify this one
		start->data_size = size;
		range->free_size -= block->data_size - size;
		return block;
	}
	// TODO Problem if 1st is freed and 2nd is realloc ? => cause free will
	free(SHIFT_BLOCK(block)); // Pb if alone
	// ft_memmove(SHIFT_BLOCK(start), SHIFT_BLOCK(block), size);
	reinit_freed_block(start, size, range);
	return start;
}

void *realloc_safe(void *ptr, size_t size) {
	t_range *range = NULL;
	t_block *block = NULL;
	void *new_ptr;

	if (!ptr || size == 0)
		return NULL; // Check is expected, size = 0 returns 32 ??

	convert_ptr(&range, &block, range, ptr);
	new_ptr = malloc(block->data_size);
	ft_memmove(new_ptr, ptr, block->data_size);
	free(ptr);

	return new_ptr;
}

// void *realloc(void *ptr, size_t size) { // Illustrate a realloc with 2 freed objects around
// 	t_range *range = get_default_range();
// 	t_block *block = NULL;
// 	t_block *start = NULL;
//
// 	convert_ptr(&range, &block, range, ptr);
// 	if (size == block->data_size)
// 		return ptr;
// 	// TODO ONLY IF IN GROUP OF size !!!
// 	size_t available_space_around = get_space_around_with_start(range,
// 	                                                            block,
// 	                                                            &start); // TODO Check doesnt break with LARGE
// 	// If need a new block
// 	if (size + sizeof(t_block) > available_space_around) {
// 		ptr = malloc(size);
// 		ft_memmove(ptr, SHIFT_BLOCK(block), block->data_size);
// 		free(SHIFT_BLOCK(block));
// 	} else if (size + sizeof(t_block) < available_space_around) { // Check and explain in the README why we sometimes don't reallocate with a different size
// 		// memmove
// 		// reange the blocks without loosing data
// 		ptr =
// 			SHIFT_BLOCK(realloc_in_freed_block(range, block, start,
// 			                                   size));
// 	}
//
// 	return ptr;
// 	// Realloc de 0
// 	// Realloc from LARGE to TINY
// 	// TODO Check  realloc doesn't break with 1 freed and 1 realloced data
// 	// TODO Make a test for the overlapping realloc in both sides
//
// 	// Case where it's stricly smaller
// 	// If smaller but no place for block (like with size-1) go for a new one (but check the freed zones next to it);
// 	// Case where it's bigger and can expand to free spaces
// 	// Case where it needs to malloc, memcpy and then unmap the old mapped zone
// 	//
//
// 	// Will probably change the type too
// 	// Need to unmap if no more
// }
