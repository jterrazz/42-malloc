/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 14:20:08 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/20 23:06:24 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_block*find_freed_block(size_t size, t_heap **found_heap)
{
    t_heap		*heap;
    t_block		*block;
    t_heap_group	group;

	heap = get_default_heap();
	group = get_heap_group_from_block_size(size);

// size_t tmp;//tmo
    while (heap) {
        block = (t_block *)SHIFT_HEAP(heap);
// tmp = heap->block_count;
        // ft_putstr("Hello a\n");

        // ft_putstr("Current heap: "); //tmp
        // ft_itoa_base((size_t)heap, 16, 9, TRUE);
        // ft_putstr(" - group: "); //tmp
        // ft_itoa_base(heap->group, 10, 0, FALSE);
        // ft_putstr(" - next: "); //tmp
        // ft_itoa_base((size_t)heap->next, 16, 9, TRUE);
        // ft_putstr("\n"); //tmp

        while (block) { // TODO should use next here
            // ft_putstr("Hello b\n");
            int temp = block->freed;
            int temp2 = (block->data_size >= size + sizeof(t_block));
            // ft_putstr("Hello c\n");


            // ft_putstr("Current block: "); //tmp
            // ft_itoa_base((size_t)block, 16, 9, TRUE);
            // ft_putstr(" - next: "); //tmp
            // ft_itoa_base((size_t)block->next, 16, 9, TRUE);
            // ft_putstr("\n"); //tmp

            if (heap->group == group) {
                // ft_putstr("Hello d\n");
                if (temp && temp2) {
                    *found_heap = heap;


                    // ft_putstr("Will replace an empty block of "); //tmp
                    // ft_itoa_base(block->data_size, 10, 0, FALSE);

                    // ft_putstr(" (plus X pf bloc size "); //tmp
                    // ft_itoa_base(sizeof(t_block), 10, 0, FALSE);
                    // ft_putstr(" )"); //tmp
                    // ft_putstr("\n"); //tmp

                    return (block);
                }
            }
            // ft_putstr("Hello d nope\n");

            block = block->next;
        }
        // ft_putstr("Finished checaking all blocks in heap\n");
        heap = heap->next;
    }
    return (NULL);
}

  t_block*fill_freed_block(size_t size)
{
    t_block	*freed_block	= NULL;
    t_heap	*freed_heap	= NULL;

    // ft_putstr("qqqqq1\n");
    freed_block = find_freed_block(size, &freed_heap);
    // ft_putstr("qqqqq2\n");
    if (freed_block && freed_heap) {
        reinit_freed_block(freed_block, size, freed_heap);
        return (freed_block);
    }
    // ft_putstr("qqqqq3\n");

    return (NULL);
}

void *start_malloc(size_t size)
{
    t_heap *heap;
    // t_block *block;

    // ft_putstr("m0");
    if (!size)
        return (NULL);

        // Maybe delete 2 * sizeof...
    size = (size + 15) & ~15; //tmp // Should print this size print in show_mem_alloc ? //Put in medium and macro for the calcccc of modulo :))))))))
    // size = (2 * sizeof(size_t) + (size + 15)) & ~15; //tmp // Should print this size print in show_mem_alloc ? //Put in medium and macro for the calcccc of modulo :))))))))

    log_call(MALLOC);

    // ft_putstr("m1");

    // put back
    // if ((block = fill_freed_block(size)) != NULL) {
    // // if ((block = fill_freed_block(size)) != NULL) {
    //     // ft_putstr("Malloc used an already created block\n");
    //     return (SHIFT_BLOCK(block));
    // }

    // ft_putstr("m2");
    if (!(heap = get_heap_of_block_size((const size_t)size))) {
        return (NULL);
    }
    // ft_putstr("Malloc got a heap\n");


    // ft_putstr("m3");
    void *ret = append_empty_block(heap, size);
    // ft_putstr("Malloc appended the block in heap\n");
    // ft_putstr("m4");
    return (ret);
}

// Put in debug bonus
void *malloc(size_t size)
{
	void *ret;

    // show_alloc_mem();


    // if (size == ((37 + 15) & ~15)) {
    //     show_alloc_mem();
    // //     int fd;
    // //     if ((fd = open(LOGS_PATH, O_CREAT | O_WRONLY | O_APPEND, 0644)) == -1)
    // //         return NULL;
    // //     ft_putstr_fd("\n\nHello\n\n", fd);
    // //     close(fd);
    // }


    pthread_mutex_lock(&g_ft_malloc_mutex);
    // ft_putstr("Malloc\n");
    ret = start_malloc(size);
    // debug_heap_block();
    if (ret) {
        log_stack(ALLOCATE, (size_t) ret, size); // Use modulo here if applicate
        // if (getenv("MyMallocScribble")) ft_memset(ret, 0xaa, size);
    }
    // ft_putstr("End malloc\n");

    pthread_mutex_unlock(&g_ft_malloc_mutex);
    return ret;
}
