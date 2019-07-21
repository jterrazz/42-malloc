/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 17:54:01 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/21 08:39:51 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_block *get_last_block_item(t_block *block) {
	while (block->next) {
		block = block->next;
	}

	return block;
}

void init_block(t_block *block, size_t size)
{
	block->prev = NULL;
	block->next = NULL;
	block->data_size = size;
	block->freed = FALSE;
}

void *append_empty_block(t_heap *heap, size_t size) {
	t_block *new_block = (t_block *)HEAP_SHIFT(heap);
	t_block *last_block = NULL;

	if (heap->block_count) {
		last_block = get_last_block_item(new_block);
		new_block = (t_block *)(BLOCK_SHIFT(last_block) + last_block->data_size);
	}
	init_block(new_block, size);
	if (heap->block_count) {
		last_block->next = new_block;
		new_block->prev = last_block;
	}
	heap->block_count++;
	heap->free_size -= (new_block->data_size + sizeof(t_block));
	return (void *) BLOCK_SHIFT(new_block);
}
