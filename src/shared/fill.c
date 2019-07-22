/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 23:47:26 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/22 11:43:57 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		divide_block(t_block *block, size_t size, t_heap *heap)
{
	t_block *free_block;

	free_block = BLOCK_SHIFT(block) + size;
	setup_block(free_block, block->next - free_block);
	free_block->freed = TRUE;
	free_block->prev = block;
	free_block->next = block->next;
	heap->block_count++;
	block->next = free_block;
	block->data_size = size;
	block->freed = FALSE;
}

/*
** Returns the filled block if one was available
*/

t_block			*try_filling_available_block(size_t size)
{
	t_block	*block;
	t_heap	*heap;

	find_available_block(size, &heap, &block);
	if (block && heap)
	{
		ft_putstr("33");
		divide_block(block, size, heap);
		ft_putstr("44");
		return (block);
	}
	return (NULL);
}
