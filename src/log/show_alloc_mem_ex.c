/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_ex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 14:17:15 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/11 15:13:19 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void print_heap_description(t_heap *heap) {
	print_heap_group(heap);
	ft_putstr(" - ");
	ft_itoa_base((size_t) heap, 16, 0, TRUE);
	ft_putstr("\n");
}

static void print_heap_hex_line(char *start) {
	ft_itoa_base((size_t) start, 16, 0, TRUE);
	unsigned int i = 0;

	while (i < 16) {
		ft_putstr(" ");
		ft_itoa_base((unsigned char) start[i], 16, 2, FALSE);
		i++;
	}
	ft_putstr("\n");
}

static void show_heap_hex_dump(t_heap *heap) {
	print_heap_description(heap);
	size_t i = 0;
	char *ptr = (char *) heap;

	while (i < heap->total_size) {
		print_heap_hex_line(ptr + i);
		i += 16;
	}
}

void show_alloc_meme_ex(void) {
	pthread_mutex_lock(&g_ft_malloc_mutex);

	t_heap *heap = g_heap_anchor;

	while (heap) {
		show_heap_hex_dump(heap);
		heap = heap->next;
	}

	pthread_mutex_unlock(&g_ft_malloc_mutex);
}
