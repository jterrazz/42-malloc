/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_default.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 19:06:00 by jterrazz          #+#    #+#             */
/*   Updated: 2019/05/22 21:54:53 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_heap**default_heap(void)
{
    static t_heap *default_heap = NULL;

    return (&default_heap);
}

t_heap*get_default_heap(void)
{
    return (*default_heap());
}

void set_default_heap(t_heap *heap)
{
    *default_heap() = heap;
}
