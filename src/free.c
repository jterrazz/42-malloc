/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 19:08:52 by jterrazz          #+#    #+#             */
/*   Updated: 2019/05/31 20:56:25 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <sys/mman.h>

void convert_ptr(t_heap **found_heap,
    t_block **found_block,
    t_heap *heap,
    void *ptr)
{
    t_block *block = NULL;

    while (heap) {
        block = (t_block *)SHIFT_HEAP(heap);
        while (block) {
            if ((void *)SHIFT_BLOCK(block) == ptr) {
                *found_heap	= heap;
                *found_block	= block;
                return;
            }
            block = block->next;
        }
        heap = heap->next;
    }
}

static void merge_prev_blocks(t_heap *heap, t_block *block)
{
    if (heap && block && block->prev && block->prev->freed) {
        block->prev->next = block->next;
        if (block->next)
            block->next->prev = block->prev;
        block->prev->data_size += block->data_size + sizeof(t_block);
        heap->block_count--;
        merge_prev_blocks(heap, block->prev);
    }
}

static void merge_next_blocks(t_heap *heap, t_block *block)
{
    if (heap && block && block->next && block->next->freed) {
        block->next = block->next->next;
        if (block->next && block->next->next) {
            block->next->next->prev	= block;
            block->data_size		+= block->next->data_size +
                                           sizeof(t_block);
        }
        heap->block_count--;
        merge_next_blocks(heap, block->next);
    }
}

void merge_near_freed_blocks(t_heap *heap, t_block *block)
{
    merge_next_blocks(heap, block);
    merge_prev_blocks(heap, block);
}

void remove_if_last_block(t_heap *heap, t_block *block)
{
    if (block->freed && !block->next) {
        if (block->prev)
            block->prev->next = NULL;
        heap->free_size += block->data_size + sizeof(t_block);
        heap->block_count--;
    }
}

void unmap_if_empty(t_heap *heap)
{
    t_heap	*static_heap	= get_default_heap();
    bool	is_last		= FALSE;
    size_t	unmap_size	= 0;

    if (heap->block_count)
        return;

    if (heap->prev)
        heap->prev->next = heap->next;

    if (heap->next)
        heap->next->prev = heap->prev;

    if ((heap == static_heap) || (!heap->next && !heap->prev)) {
        if (!heap->block_count)
            is_last = TRUE;
        unmap_size = heap->total_size;
        set_default_heap(heap->next);
    }
    if (is_last)
        munmap(heap, unmap_size);
}

void free(void *ptr)
{
    t_heap	*heap	= get_default_heap();
    t_block	*block	= NULL;
    if (!ptr || !heap)
        return;

    convert_ptr(&heap, &block, heap, ptr);

    if (block && heap) {
        block->freed = TRUE;
        merge_near_freed_blocks(heap, block);
        remove_if_last_block(heap, block);
        unmap_if_empty(heap);
    }
}
