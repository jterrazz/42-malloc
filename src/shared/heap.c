/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 16:06:12 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/21 15:03:40 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void *append_empty_block(t_heap *heap, size_t size) {
	t_block *new_block = (t_block *)HEAP_SHIFT(heap);
	t_block *last_block = NULL;

	if (heap->block_count) {
		last_block = get_last_block(new_block);
		new_block = (t_block *)(BLOCK_SHIFT(last_block) + last_block->data_size);
	}
	setup_block(new_block, size);
	if (heap->block_count) {
		last_block->next = new_block;
		new_block->prev = last_block;
	}
	heap->block_count++;
	heap->free_size -= (new_block->data_size + sizeof(t_block));
	return (void *) BLOCK_SHIFT(new_block);
}

static rlim_t get_system_limit() {
    struct rlimit rpl;

    if (getrlimit(RLIMIT_DATA, &rpl) < 0)
        return (-1);

    return rpl.rlim_max;
}

t_heap *create_heap(t_heap_group group, size_t block_size)
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

    ft_bzero(heap, sizeof(heap));
    heap->group		= group;
    heap->total_size	= heap_size;
    heap->free_size	= heap_size - sizeof(t_heap);

	log_detail(HEAP_CREATE);

    return (heap);
}

static t_bool is_last_of_preallocated(t_heap *heap)
{
	t_heap	*static_heap	= g_heap_anchor;
	t_heap_group group = heap->group;

	int i = 0;
	while (static_heap)
	{
		if (static_heap->group == group)
			i++;
		static_heap = static_heap->next;
	}
	return (i == 1);
}

void delete_heap_if_empty(t_heap *heap)
{
    t_heap	*static_heap	= g_heap_anchor;

    if (heap->block_count)
        return;

    if (heap->prev)
        heap->prev->next = heap->next;
    if (heap->next)
        heap->next->prev = heap->prev;

    if (!is_last_of_preallocated(heap)) {
		if (heap == static_heap)
			g_heap_anchor = heap->next;
        munmap(heap, heap->total_size);
		log_detail(HEAP_DELETE);
    }
}
