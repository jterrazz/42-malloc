/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 19:08:52 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/20 23:06:22 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <sys/mman.h>

void debug_heap_block()
{
    t_heap		*heap;
    t_block		*block;

    heap = get_default_heap();

    ft_putstr("\n\nHEAP STATUS\n"); //tmp
    while (heap) {
        block = (t_block *)SHIFT_HEAP(heap);

        ft_putstr("Heap: "); //tmp
        ft_itoa_base((size_t)heap, 16, 9, TRUE);
        ft_putstr(" - group: "); //tmp
        ft_itoa_base(heap->group, 10, 0, FALSE);
        ft_putstr(" - next: "); //tmp
        ft_itoa_base((size_t)heap->next, 16, 9, TRUE);
        ft_putstr("\n"); //tmp

        while (block) {
            ft_putstr("Block: "); //tmp
            ft_itoa_base((size_t)block, 16, 9, TRUE);
            ft_putstr(" - next: "); //tmp
            ft_itoa_base((size_t)block->next, 16, 9, TRUE);
            ft_putstr("\n"); //tmp

            block = block->next;
        }
        ft_putstr("Finished status\n");
        heap = heap->next;
    }
}

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


            // ft_putstr("EL heap: "); //tmp
            // ft_itoa_base((size_t)heap, 16, 9, TRUE);
            // ft_putstr(" - block: "); //tmp
            // ft_itoa_base((size_t)block, 16, 9, TRUE);
            // ft_putstr(" - next block: "); //tmp
            // ft_itoa_base((size_t)block->next, 16, 9, TRUE);
            // ft_putstr("\n"); //tmp


            block = block->next;
            // ft_putstr("hm3");
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
        // merge_prev_blocks(heap, block->prev);
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
        // merge_next_blocks(heap, block->next);
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
        block->data_size = 0;
        block->prev = NULL;
        // block->next = NULL;
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

    // if (heap == static_heap)
        // set_default_heap(heap->next);


    // if (!heap->next && !heap->prev){}
    // else
    //     munmap(heap, heap->total_size);

    if ((heap == static_heap) || (!heap->next && !heap->prev)) {
        if (!heap->block_count)
            is_last = TRUE;
        set_default_heap(heap->next);
    }
    if (is_last) // Don't delete if last preallocated
        munmap(heap, heap->total_size);
}

 void start_free(void *ptr)
{

    // ft_putstr("freeww\n");
    t_heap	*heap	= get_default_heap();
    // ft_putstr("free0\n");
    t_block	*block	= NULL;
    // ft_putstr("free1\n");

    if (!ptr || !heap)
        return;
    // ft_putstr("fre2\n");
    convert_ptr(&heap, &block, heap, ptr);
    // ft_putstr("free3\n");

    if (block && heap) {
        block->freed = TRUE;
        // if (getenv("MyMallocScribble")) ft_memset(ptr, 0x55, block->data_size);
        // ft_putstr("free4\n");

        t_block *ret = merge_near_freed_blocks(heap, block);
        block = ret ? ret : block;

        // ft_putstr("free5\n");
        remove_if_last_block(heap, block);
        // ft_putstr("free6\n");
        unmap_if_empty(heap);
        // ft_putstr("free7\n");
    }
}

void free(void *ptr)
{
    // show_alloc_mem();
    pthread_mutex_lock(&g_ft_malloc_mutex);
    // ft_putstr("Free\n");
    log_call(FREE);
    log_stack(DEALLOCATE, (size_t) ptr, 0);
    // ft_putstr("a0");
    start_free(ptr);
    // debug_heap_block();
    // ft_putstr("End of free");
    // ft_putstr("End of free\n");
    pthread_mutex_unlock(&g_ft_malloc_mutex);
    // ft_putstr("Real end of free");
}
