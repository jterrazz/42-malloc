/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 19:08:52 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/21 10:05:50 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

// rename to find state
void convert_ptr(t_heap **found_heap,
    t_block **found_block,
    t_heap *heap,
    void *ptr)
{
    t_block *block = NULL;

    while (heap) {
        block = (t_block *)SHIFT_HEAP(heap);
        while (block) {
            if (SHIFT_BLOCK(block) == ptr) {
                *found_heap	= heap;
                *found_block	= block;
                return;
            }

            block = block->next;
        }
        heap = heap->next;
    }
}

// Should return block to the left freed
static t_block *merge_prev_blocks(t_heap *heap, t_block *block)
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

static void merge_next_blocks(t_heap *heap, t_block *block)
{
    if (heap && block && block->next && block->next->freed) {
        block->data_size += block->next->data_size + sizeof(t_block);
        if (block->next && block->next->next) {
            block->next->next->prev	= block;
        }
        block->next = block->next->next;
        heap->block_count--;
    }
}

t_block *merge_near_freed_blocks(t_heap *heap, t_block *block)
{
    merge_next_blocks(heap, block);
    return merge_prev_blocks(heap, block);
}

void remove_if_last_block(t_heap *heap, t_block *block)
{
    if (block->freed && !block->next) {
        if (block->prev) {
            block->prev->next = NULL;
        }
        heap->free_size += block->data_size + sizeof(t_block);
        heap->block_count--;
    }
}

void unmap_if_empty(t_heap *heap)
{
    t_heap	*static_heap	= get_default_heap();

    if (heap->block_count)
        return;

    if (heap->prev)
        heap->prev->next = heap->next;
    if (heap->next)
        heap->next->prev = heap->prev;

    if (heap == static_heap) { // Don't delete if last preallocated
        set_default_heap(heap->next);
        munmap(heap, heap->total_size);
    }
}

 void start_free(void *ptr)
{

    t_heap	*heap	= get_default_heap();
    t_block	*block	= NULL;
    t_block *ret;

    if (!ptr || !heap)
        return;
    convert_ptr(&heap, &block, heap, ptr);

    if (block && heap) {
        block->freed = TRUE;

        if (getenv_cached(ENV_SCRIBBLE))
            ft_memset(ptr, 0x55, block->data_size);

        ret = merge_near_freed_blocks(heap, block);
        block = ret ? ret : block;
        remove_if_last_block(heap, block);
        unmap_if_empty(heap);
    }
}

// Log mmap and munmap too
void free(void *ptr)
{
    pthread_mutex_lock(&g_ft_malloc_mutex);
    log_call(FREE);
    start_free(ptr);
    log_stack(DEALLOCATE, (size_t) ptr, 0);
    pthread_mutex_unlock(&g_ft_malloc_mutex);
}
