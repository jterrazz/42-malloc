/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:06:42 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/21 15:10:10 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static size_t print_block_list(t_block *block)
{
    char	*start_address;
    char	*end_address;
    size_t	total;

    total		= 0;
    start_address	= NULL;
    end_address		= NULL;

    while (block) {
        start_address	= (char *)BLOCK_SHIFT(block);
        end_address	= start_address + block->data_size;

        if (!block->freed) {
            ft_itoa_base((size_t)start_address, 16, 9, TRUE);
            ft_putstr(" - ");
            ft_itoa_base((size_t)end_address, 16, 9, TRUE);
            ft_putstr(" : ");
            ft_itoa_base(block->data_size, 10, 0, FALSE);
            ft_putstr(" octets\n");
            total += block->data_size;
        }

        block = block->next;
    }
    return (total);
}

static void print_heap_header(char *name, t_heap *heap)
{
    ft_putstr(name);
    ft_putstr(" : ");
    ft_itoa_base((size_t)heap, 16, 9, TRUE);
    ft_putstr("\n");
}

void start_show_alloc_mem()
{
    t_heap	*first_heap;
    t_heap	*last_heap;
    size_t	total;

    total	= 0;
    first_heap	= g_heap_anchor;
    last_heap	= get_last_heap(first_heap);

    while (last_heap) {
        if (last_heap->group == TINY) {
            print_heap_header("TINY", last_heap);
        } else if (last_heap->group == SMALL) {
            print_heap_header("SMALL", last_heap);
        } else {
            print_heap_header("LARGE", last_heap);
        }

        if (last_heap->block_count)
            total += print_block_list((t_block *)HEAP_SHIFT(last_heap));
        last_heap = last_heap->prev;
    }

    ft_putstr("Total : ");
    ft_itoa_base(total, 10, 0, FALSE);
    ft_putstr(" octets\n");
}

void show_alloc_mem()
{
    pthread_mutex_lock(&g_ft_malloc_mutex);
    start_show_alloc_mem();
    pthread_mutex_unlock(&g_ft_malloc_mutex);
}
