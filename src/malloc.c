/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 14:20:08 by jterrazz          #+#    #+#             */
/*   Updated: 2019/04/26 16:13:24 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Check all includes and forbidden fts
// Make graph to show how memory behave
// Handle malloc errors
// TODO Malloc de 0 et de 1 en test
// TODO Malloc negatif
// Size_t long ou int

#include "malloc.h"
// TODO Prevoir les int max overflows avec blcok et le reste

void reinit_freed_block(t_block *block, size_t size, t_range *range) { // TODO Move to files
	t_block *freed_block = (t_block *) (SHIFT_BLOCK(block) + size);

	init_empty_block(freed_block, block->data_size - size - sizeof(t_block));
	freed_block->freed = TRUE;
	block->freed = FALSE;
	block->data_size = size;

	freed_block->prev = block;
	freed_block->next = block->next;
	block->next = freed_block;

	range->block_count++;
	range->free_size -= size; // TODO Check that ???
}

static t_block *find_freed_block(size_t size, t_range **found_range) {
	t_range *range = get_default_range();
	t_block *block;
	t_range_group group = get_range_group_from_block_size(size);

	while (range) {
		block = (t_block *) SHIFT_RANGE(range);
		while (block && range->group == group) {
			if (block->freed && (block->data_size >= size + sizeof(t_block))) {
				*found_range = range;
				return block;
			}
			block = block->next;
		}
		range = range->next;
	}
	return NULL;
}

static t_block *fill_freed_block(size_t size) {
	t_block *freed_block = NULL;
	t_range *freed_range = NULL;

	freed_block = find_freed_block(size, &freed_range);
	if (freed_block && freed_range) {
		reinit_freed_block(freed_block, size, freed_range);
		return freed_block;
	}

	return NULL;
}

void *malloc(size_t size) {
	t_block *block = NULL;
	// ft_putstr("Malloc start\n");

	if (!size)
		return NULL;
	block = fill_freed_block(size);
	if (block) {
		return SHIFT_BLOCK(block);
	}

	t_range *range = get_range_of_block_size((const size_t) size);
	if (!range)
		return NULL;
	// ft_putstr("Malloc soon end\n");
	return append_empty_block(range, size);
}
