/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_heap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 01:57:33 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/21 15:10:26 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void print_heap_group(t_heap *heap)
{
    if (heap->group == TINY) {
        ft_putstr("TINY");
    } else if (heap->group == SMALL) {
        ft_putstr("SMALL");
    } else {
        ft_putstr("LARGE");
    }
}
