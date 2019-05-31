/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 17:13:09 by jterrazz          #+#    #+#             */
/*   Updated: 2019/05/31 18:22:05 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <unistd.h>

t_range_group get_range_group_from_block_size(size_t size)
{
    if (size <= (size_t) TINY_BLOCK_SIZE)
        return (TINY);
    else if (size <= (size_t) SMALL_BLOCK_SIZE)
        return (SMALL);

    return (LARGE);
}

size_t get_range_size_from_block_size(size_t size)
{
    t_range_group range_group = get_range_group_from_block_size(size);

    if (range_group == TINY)
        return ((size_t) TINY_RANGE_ALLOCATION_SIZE);
    else if (range_group == SMALL)
        return ((size_t) SMALL_RANGE_ALLOCATION_SIZE);

    return (size + sizeof(t_range) + sizeof(t_block));
}
