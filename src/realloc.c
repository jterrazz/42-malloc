/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 17:44:52 by jterrazz          #+#    #+#             */
/*   Updated: 2019/05/22 22:01:07 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
 realloc of 0 ?
 if (size == 0) // Should it free the pointer ?
*/

void*realloc(void *ptr, size_t size)
{
    t_range	*range;
    t_block	*block;
    void	*new_ptr;
    size_t	data_size;

    if (!ptr)
        return (malloc(size));

    range = get_default_range();
    convert_ptr(&range, &block, range, ptr);
    if (!range || !block)
        return (malloc(size));

    if (size == block->data_size)
        return (ptr);

    data_size = block->data_size > size ? size : block->data_size;

    new_ptr = malloc(size);
    ft_memmove(new_ptr, ptr, data_size);
    free(ptr);

    return (new_ptr);
}
