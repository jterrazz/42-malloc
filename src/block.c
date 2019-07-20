/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 17:54:01 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/17 21:42:14 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_block *get_last_block_item(t_block *block) {
	while (block->next) {
		block = block->next;
	}

	return block;
}

static void init_empty_block(t_block *block, size_t size) {
	block->prev = NULL;
	block->next = NULL;
	block->data_size = size;
	block->freed = FALSE;
}

void reinit_freed_block(t_block *block, size_t size, t_heap *heap) {
	t_block *freed_block = (t_block *) (SHIFT_BLOCK(block) + size);

	init_empty_block(freed_block, block->data_size - size - sizeof(t_block));
	// init_empty_block(freed_block, block->data_size - size - sizeof(t_block));
	freed_block->freed = TRUE;
	block->freed = FALSE;
	block->data_size = size;
	freed_block->prev = block;
	freed_block->next = block->next;
	block->next = freed_block;
	heap->block_count++;
	heap->free_size -= size;
}

void *append_empty_block(t_heap *heap, size_t size) {
	t_block *new_block = (t_block *)SHIFT_HEAP(heap);
	t_block *last_block = NULL;

	if (heap->block_count) {
		last_block = get_last_block_item(new_block);
		new_block =
			(t_block *)(SHIFT_BLOCK(last_block) +
			            last_block->data_size);
	}
	init_empty_block(new_block, size);
	if (heap->block_count) {
		last_block->next = new_block;
		new_block->prev = last_block;
	}
	heap->block_count++;
	heap->free_size =
		heap->free_size - new_block->data_size - sizeof(t_block);
	return (void *) SHIFT_BLOCK(new_block);
}
