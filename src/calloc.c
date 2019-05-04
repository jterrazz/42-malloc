/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 14:42:17 by jterrazz          #+#    #+#             */
/*   Updated: 2019/05/04 01:37:18 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

// Put data to 0 in realloc// Implements overflows with example from C implemeentation
// realloc dedicated for calloc ?
void *calloc(size_t count, size_t size) { // If count = 0
	size_t malloc_size = size * count;
	if (malloc_size < 32) {
		malloc_size = 32;
	}
	void *ptr = NULL;

	// Check if result is bigger than size_t_max ?
	ptr = malloc(malloc_size);
	if (ptr)
		ft_bzero(ptr, malloc_size);
	return ptr;
}
