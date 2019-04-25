/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 14:42:17 by jterrazz          #+#    #+#             */
/*   Updated: 2019/04/25 18:51:14 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void *calloc(size_t count, size_t size) { // If count = 0
	size_t malloc_size = size == 0 ? count * 32 : size * count;
	void *ptr = NULL;
	// ft_putstr("Calloc here\n");

	// Check if result is bigger than size_t_max ?
	ptr = malloc(malloc_size);
	// Fill with 0
	if (ptr)
		ft_bzero(ptr, malloc_size);
	return ptr;
}
