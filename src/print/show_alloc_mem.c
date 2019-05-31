/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:06:42 by jterrazz          #+#    #+#             */
/*   Updated: 2019/05/31 20:54:33 by jterrazz         ###   ########.fr       */
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
        start_address	= (char *)SHIFT_BLOCK(block);
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

static void print_range_header(char *name, t_range *range)
{
    ft_putstr(name);
    ft_putstr(" : ");
    ft_itoa_base((size_t)range, 16, 9, TRUE);
    ft_putstr("\n");
}

void show_alloc_mem()
{
    t_range	*first_range;
    t_range	*last_range;
    size_t	total;

    total	= 0;
    first_range = get_default_range();
    last_range	= get_last_range(first_range);

    while (last_range) {
        if (last_range->group == TINY) {
            print_range_header("TINY", last_range);
        } else if (last_range->group == SMALL) {
            print_range_header("SMALL", last_range);
        } else {
            print_range_header("LARGE", last_range);
        }

        if (last_range->block_count)
            total += print_block_list((t_block *)SHIFT_RANGE(last_range));
        last_range = last_range->prev;
    }

    ft_putstr("Total : ");
    ft_itoa_base(total, 10, 0, FALSE);
    ft_putstr(" octets\n");
}
