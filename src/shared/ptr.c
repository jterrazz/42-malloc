/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 11:10:32 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/21 11:14:12 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void search_ptr(t_heap **ptr_heap, t_block **ptr_block, t_heap *heap, void *ptr)
{
    t_block *block = NULL;

    while (heap) {
        block = (t_block *)HEAP_SHIFT(heap);

        while (block) {
            if (BLOCK_SHIFT(block) == ptr) {
                *ptr_heap	= heap;
                *ptr_block	= block;
                return;
            }
            block = block->next;
        }
        heap = heap->next;
    }
}
