/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 14:42:17 by jterrazz          #+#    #+#             */
/*   Updated: 2019/04/26 16:13:34 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void *calloc(size_t count, size_t size) { // If count = 0
	// ft_putstr("Calloc start\n");
	// ft_putstr("Count\n");
	// ft_itoa_base(count, 10, 0);
	// ft_putstr("\n");
	// ft_putstr("Size\n");
	// ft_itoa_base(size, 10, 0);
	// ft_putstr("\n");
	// size_t malloc_size = size == 0 ? count * 32 : size * count;
	if (count == 0)
		count = 1;
	if (size == 0)
		size = 32;

	size_t malloc_size = size * count;
	void *ptr = NULL;

	// Check if result is bigger than size_t_max ?
	ptr = malloc(malloc_size);
	// Fill with 0
	if (ptr)
		ft_bzero(ptr, malloc_size);
	// ft_putstr("Calloc end\n");
	return ptr;
}
