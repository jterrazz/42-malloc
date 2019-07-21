/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 17:54:01 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/21 15:10:44 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block*get_last_block(t_block *block)
{
    while (block->next) {
        block = block->next;
    }

    return (block);
}

void find_available_block(size_t size, t_heap **res_heap, t_block **res_block)
{
    t_heap		*heap;
    t_block		*block;
    t_heap_group	group;

    heap	= g_heap_anchor;
    group	= get_heap_group_from_block_size(size);

    while (heap) {
        block = (t_block *)HEAP_SHIFT(heap);

        while (heap->group == group && block) {
            if (block->freed && (block->data_size >= size + sizeof(t_block))) {
                *res_heap	= heap;
                *res_block	= block;
                return;
            }
            block = block->next;
        }
        heap = heap->next;
    }

    *res_heap	= NULL;
    *res_block	= NULL;
}
