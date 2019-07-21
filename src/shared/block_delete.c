/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_delete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 10:12:22 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/21 11:19:18 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_block *merge_prev_block(t_heap *heap, t_block *block)
{
    if (heap && block && block->prev && block->prev->freed) {
        block->prev->next = block->next;
        if (block->next)
            block->next->prev = block->prev;
        block->prev->data_size += block->data_size + sizeof(t_block);
        heap->block_count--;
        return block->prev;
    }
    return NULL;
}

static void merge_next_block(t_heap *heap, t_block *block)
{
    if (heap && block && block->next && block->next->freed) {
        block->data_size += block->next->data_size + sizeof(t_block);
        if (block->next && block->next->next)
            block->next->next->prev	= block;
        block->next = block->next->next;
        heap->block_count--;
    }
}

t_block *merge_block(t_heap *heap, t_block *block)
{
    merge_next_block(heap, block);
    return merge_prev_block(heap, block);
}

void remove_block_if_last(t_heap *heap, t_block *block)
{
    if (block->freed && !block->next) {
        if (block->prev)
            block->prev->next = NULL;
        heap->free_size += block->data_size + sizeof(t_block);
        heap->block_count--;
    }
}
