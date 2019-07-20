/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 16:06:12 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/20 08:42:04 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <sys/resource.h>
#include "malloc.h"

t_heap*get_last_heap(t_heap *heap)
{
    if (!heap)
        return (NULL);

    while (heap->next) {
        heap = heap->next;
    }

    return (heap);
}

static t_heap*find_available_heap(const t_heap *list_start,
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

static rlim_t get_system_limit() {
    struct rlimit rpl;

    if (getrlimit(RLIMIT_DATA, &rpl) < 0)
        return (-1);

    return rpl.rlim_max;
}

static t_heap*new_heap(t_heap_group group, size_t block_size)
{
    size_t	heap_size;
    t_heap	*heap;

    heap_size = get_heap_size_from_block_size(block_size);
    if (heap_size > get_system_limit())
        return (NULL);

    heap = (t_heap *)mmap(NULL, heap_size,
        PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);

    if (heap == MAP_FAILED)
        return (NULL);

    heap->prev		= NULL;
    heap->next		= NULL;
    heap->group		= group;
    heap->block_count	= 0;
    heap->total_size	= heap_size;
    heap->free_size	= heap_size - sizeof(t_heap);

    return (heap);
}

t_heap*get_heap_of_block_size(const size_t size)
{
    t_heap		*default_heap;
    t_heap_group	heap_group;
    t_heap		*heap;

    default_heap	= get_default_heap();
    heap_group		= get_heap_group_from_block_size(size);
    heap		= find_available_heap(default_heap,
        heap_group,
        size + sizeof(t_block));

    if (heap == NULL) {
        if (!(heap = new_heap(heap_group, size)))
            return (NULL);

        heap->next = (t_heap *)default_heap;
        if (heap->next) {
            heap->next->prev = heap;
        }
        set_default_heap(heap);
    }

    return (heap);
}
