/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 17:44:52 by jterrazz          #+#    #+#             */
/*   Updated: 2019/05/31 20:31:29 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void*realloc(void *ptr, size_t size)
{
    t_heap	*heap;
    t_block	*block;
    void	*new_ptr;
    size_t	data_size;

    if (!ptr)
        return (malloc(size));
    if (!size)
        return (ptr);

    heap = get_default_heap();
    convert_ptr(&heap, &block, heap, ptr);
    if (!heap || !block)
        return (malloc(size));

    if (size == block->data_size)
        return (ptr);

    data_size = block->data_size > size ? size : block->data_size;

    new_ptr = malloc(size);
    ft_memmove(new_ptr, ptr, data_size);
    free(ptr);

    return (new_ptr);
}
