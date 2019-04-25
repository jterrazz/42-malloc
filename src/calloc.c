/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 14:42:17 by jterrazz          #+#    #+#             */
/*   Updated: 2019/04/25 15:01:42 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void *calloc(size_t count, size_t size) {
	size_t malloc_size = size * count;

	// Check if result is bigger than size_t_max ?
	void *ptr = malloc(malloc_size);
	// Fill with 0
	// ft_bzero(ptr, malloc_size);
	return ptr;
}
