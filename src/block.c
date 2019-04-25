/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 17:54:01 by jterrazz          #+#    #+#             */
/*   Updated: 2019/04/25 18:19:24 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_block *get_last_block_item(t_block *block) {
	while (block->next) {
		block = block->next;
	}

	return block;
}

void init_empty_block(t_block *block, size_t size) {
	block->prev = NULL;
	block->next = NULL;
	block->data_size = size;
	block->freed = FALSE;
}

void *append_empty_block(t_range *range, size_t size) {
	t_block *new_block = (t_block *)SHIFT_RANGE(range);
	t_block *last_block = NULL;

	if (range->block_count) {
		last_block = get_last_block_item(new_block);
		new_block =
			(t_block *)(SHIFT_BLOCK(last_block) +
			            last_block->data_size);
		// TODO Check I dont need to cast to char
	}
	init_empty_block(new_block, size);
	if (range->block_count) {
		last_block->next = new_block;
		new_block->prev = last_block;
	}
	range->block_count++;
	range->free_size =
		range->free_size - new_block->data_size - sizeof(t_block);
	return (void *) SHIFT_BLOCK(new_block);
}
