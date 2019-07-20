/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 19:08:52 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/20 15:24:00 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <sys/mman.h>

// rename to find state
void convert_ptr(t_heap **found_heap,
    t_block **found_block,
    t_heap *heap,
    void *ptr)
{
    t_block *block = NULL;

    // ft_putstr("hm0");
    while (heap) {
        block = (t_block *)SHIFT_HEAP(heap);
        while (block) {
            // ft_putstr("hm1");
            // if ((void *)block > (void *) heap + heap->total_size) // should not be needed
            //     return;
            if (SHIFT_BLOCK(block) == ptr) {
                *found_heap	= heap;
                *found_block	= block;
                // ft_putstr("hm2");
                return;
            }
            // ft_putstr("hmrrrr");
            block = block->next;
            // ft_putstr("hm3");
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
        block->data_size += block->next->data_size + sizeof(t_block);
        if (block->next && block->next->next) {
            block->next->next->prev	= block;
        }
        block->next = block->next->next;
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

    if (heap->block_count)
        return;

    if (heap->prev)
        heap->prev->next = heap->next;

    if (heap->next)
        heap->next->prev = heap->prev;

    if ((heap == static_heap) || (!heap->next && !heap->prev)) {
        if (!heap->block_count)
            is_last = TRUE;
        set_default_heap(heap->next);
    }
    if (is_last)
        munmap(heap, heap->total_size);
}

void ft_free(void *ptr)
{

    t_heap	*heap	= get_default_heap();
    t_block	*block	= NULL;

    if (!ptr || !heap)
        return;
    // ft_putstr("r0");
    convert_ptr(&heap, &block, heap, ptr);
    // ft_putstr("r1");

    if (block && heap) {
        block->freed = TRUE;
        // if (getenv("MyMallocScribble")) ft_memset(ptr, 0x55, block->data_size);
        // ft_putstr("t0");
        merge_near_freed_blocks(heap, block);
        // ft_putstr("t1");
        remove_if_last_block(heap, block);
        // ft_putstr("t2");
        unmap_if_empty(heap);
        // ft_putstr("t3");
    }
}

void free(void *ptr)
{
    // ft_putstr("Free\n");
    // show_alloc_mem();
    pthread_mutex_lock(&g_ft_malloc_mutex);
    log_call(FREE);
    log_stack(DEALLOCATE, (size_t) ptr, 0);
    // ft_putstr("a0");
    ft_free(ptr);
    // ft_putstr("End of free");
    pthread_mutex_unlock(&g_ft_malloc_mutex);
    // ft_putstr("Real end of free");
}
