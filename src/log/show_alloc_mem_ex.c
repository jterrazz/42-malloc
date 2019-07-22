/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_ex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 14:17:15 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/22 10:48:05 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	print_heap_description(t_heap *heap)
{
	print_heap_group(heap);
	ft_putstr(" - ");
	ft_itoa_base((size_t)heap, 16, 0, TRUE);
	ft_putstr("\n");
}

static void	print_heap_hex_line(char *start)
{
	uint8_t i;

	i = 0;
	ft_itoa_base((size_t)start, 16, 0, TRUE);
	while (i < 16)
	{
		ft_putstr(" ");
		ft_itoa_base((unsigned char)start[i], 16, 2, FALSE);
		i++;
	}
	ft_putstr("\n");
}

static void	start_show_alloc_mem_hex(void)
{
	t_heap	*heap;
	size_t	i;
	char	*ptr;

	heap = g_heap_anchor;
	while (heap)
	{
		print_heap_description(heap);
		i = 0;
		ptr = (char *)heap;
		while (i < heap->total_size)
		{
			print_heap_hex_line(ptr + i);
			i += 16;
		}
		heap = heap->next;
	}
}

void		show_alloc_mem_hex(void)
{
	pthread_mutex_lock(&g_ft_malloc_mutex);
	start_show_alloc_mem_hex();
	pthread_mutex_unlock(&g_ft_malloc_mutex);
}
