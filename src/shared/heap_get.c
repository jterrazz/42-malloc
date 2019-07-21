/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 10:58:50 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/21 15:02:42 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_heap*get_available_heap(const t_heap *list_start,
    const t_heap_group group,
    const size_t required_size)
{
    t_heap *heap_el = (t_heap *)list_start;

    while (heap_el) {
        if ((heap_el->group == group) &&
            (heap_el->free_size >= required_size))
            return (heap_el);

        heap_el = heap_el->next;
    }
    return (NULL);
}

t_heap*get_heap_of_block_size(const size_t size)
{
    t_heap		*default_heap;
    t_heap_group	heap_group;
    t_heap		*heap;

    default_heap	= g_heap_anchor;
    heap_group		= get_heap_group_from_block_size(size);
    heap		= get_available_heap(default_heap,
        heap_group,
        size + sizeof(t_block));

    if (heap == NULL) {
        if (!(heap = create_heap(heap_group, size)))
            return (NULL);

        heap->next = (t_heap *)default_heap;
        if (heap->next) {
            heap->next->prev = heap;
        }
        g_heap_anchor = heap;
    }

    return (heap);
}

t_heap*get_last_heap(t_heap *heap)
{
    if (!heap)
        return (NULL);

    while (heap->next)
        heap = heap->next;

    return (heap);
}
