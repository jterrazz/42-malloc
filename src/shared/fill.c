/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 23:47:26 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/20 23:49:14 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
// Add description on top of main functions + add this in the todo file

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
