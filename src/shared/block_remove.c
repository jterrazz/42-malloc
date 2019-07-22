/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_remove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 11:24:18 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/22 10:53:38 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	remove_block_if_last(t_heap *heap, t_block *block)
{
	if (block->freed && !block->next)
	{
		if (block->prev)
			block->prev->next = NULL;
		heap->free_size += block->data_size + sizeof(t_block);
		heap->block_count--;
	}
}
