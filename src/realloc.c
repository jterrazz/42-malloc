/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 17:44:52 by jterrazz          #+#    #+#             */
/*   Updated: 2019/05/04 01:55:23 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void *realloc(void *ptr, size_t size) {
	t_range *range = get_default_range();
	t_block *block = NULL;
	void *new_ptr;

	if (!size)
		size = 32; // Maybe not ?
	if (!ptr)
		return malloc(size); // Check if 0
		// if (size == 0) // Should it free the pointer ?
		// 	return NULL; // Check is expected, size = 0 returns 32 ??
	// if (size == 0) {
	// 	free(ptr);
	// 	return malloc(32); // What is minimum sized object ?
	// }

	convert_ptr(&range, &block, range, ptr);

	if (!range || !block)
		return malloc(size); // Return null or pointer ?
	if (size == block->data_size)
		return ptr;

	size_t data_size = block->data_size > size ? size : block->data_size;

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
// Need to unmap if no more /\?
// Illustrate a realloc with 2 freed objects around
