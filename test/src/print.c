/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 18:47:07 by jterrazz          #+#    #+#             */
/*   Updated: 2019/05/31 18:29:16 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "./test.h"

void show_range_list()
{
    int i = 0;
    t_range *range = get_default_range();

    printf("DEBUG: Range list\n");

    while (range) {
        printf(
            "%d. Range %p, prev: %p, next: %p (count: %zu, group: %d, total size: %zu, free_space: %zu)\n",
            i,
            range,
            range->prev,
            range->next,
            range->block_count,
            range->group,
            range->total_size,
            range->free_size);
        range = range->next;
        i++;
    }
}
