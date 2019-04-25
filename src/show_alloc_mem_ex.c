/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_ex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 14:17:15 by jterrazz          #+#    #+#             */
/*   Updated: 2019/04/25 15:02:06 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void print_range_description(t_range *range) {
	print_range_group(range);
	ft_putstr(" - ");
	ft_itoa_base((size_t) range, 16, 0);
	ft_putstr("\n");
}

static void print_range_hex_line(char *start) {
	ft_itoa_base((size_t) start, 16, 0);
	unsigned int i = 0;

	while (i < 16) {
		ft_putstr(" ");
		ft_itoa_base((unsigned char) start[i], 16, 2);
		i++;
	}
	ft_putstr("\n");
}

static void show_range_hex_dump(t_range *range) {
	print_range_description(range);
	size_t i = 0;
	char *ptr = (char *) range;

	while (i < range->total_size) {
		print_range_hex_line(ptr + i);
		i += 16;
	}
}

void show_alloc_meme_ex(void) {
	t_range *range = get_default_range();

	while (range) {
		show_range_hex_dump(range);
		range = range->next;
	}
}
