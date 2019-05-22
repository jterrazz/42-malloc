/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 14:20:08 by jterrazz          #+#    #+#             */
/*   Updated: 2019/05/22 21:49:29 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_block*find_freed_block(size_t size, t_range **found_range)
{
    t_range		*range;
    t_block		*block;
    t_range_group	group;

	range = get_default_range();
	group = get_range_group_from_block_size(size);

    while (range) {
        block = (t_block *)SHIFT_RANGE(range);
        while (block && range->group == group) {
            if (block->freed && (block->data_size >= size + sizeof(t_block))) {
                *found_range = range;
                return (block);
            }
            block = block->next;
        }
        range = range->next;
    }
    return (NULL);
}

static t_block*fill_freed_block(size_t size)
{
    t_block	*freed_block	= NULL;
    t_range	*freed_range	= NULL;

    freed_block = find_freed_block(size, &freed_range);
    if (freed_block && freed_range) {
        reinit_freed_block(freed_block, size, freed_range);
        return (freed_block);
    }

    return (NULL);
}

void*malloc(size_t size)
{
    t_block *block = NULL;

    // mmalloc 0 = 32 ?

    if (!size)  // check ????
        return (NULL);

    block = fill_freed_block(size);
    if (block) {
        return (SHIFT_BLOCK(block));
    }

    t_range *range = get_range_of_block_size((const size_t)size);
    if (!range)
        return (NULL);

    return (append_empty_block(range, size));
}
