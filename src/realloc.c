/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 17:44:52 by jterrazz          #+#    #+#             */
/*   Updated: 2019/04/25 18:17:50 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
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
// }

void *realloc(void *ptr, size_t size) {
	// ft_putstr("Realloc here\n");
	t_range *range = get_default_range();
	t_block *block = NULL;
	void *new_ptr;

	if (!ptr)
		return malloc(size); // Check if 0
		// if (size == 0) // Should it free the pointer ?
		// 	return NULL; // Check is expected, size = 0 returns 32 ??
	if (size == 0) {
		free(ptr);
		return malloc(32); // What is minimum sized object ?
	}

	convert_ptr(&range, &block, range, ptr);

	if (!range || !block)
		return NULL; // Return null or pointer ?
	if (size == block->data_size)
		return ptr;

	size_t data_size = block->data_size > size ? size : block->data_size;

	ptr = malloc(size);
	new_ptr = malloc(size);
	ft_memmove(new_ptr, ptr, data_size);
	free(ptr);

	return new_ptr;
}

// TODO Check  realloc doesn't break with 1 freed and 1 realloced data
// TODO Make a test for the overlapping realloc in both sides

// Case where it's stricly smaller
// If smaller but no place for block (like with size-1) go for a new one (but check the freed zones next to it);
// Case where it's bigger and can expand to free spaces
// Case where it needs to malloc, memcpy and then unmap the old mapped zone
//

// Will probably change the type too
// Need to unmap if no more
// Illustrate a realloc with 2 freed objects around
