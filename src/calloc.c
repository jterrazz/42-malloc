/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 14:42:17 by jterrazz          #+#    #+#             */
/*   Updated: 2019/05/22 21:43:53 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
SPECIAL CASES
If count = 0
if size < 32 ??
*/

void*calloc(size_t count, size_t size)
{
    size_t malloc_size;
	void *ptr;

    malloc_size = size * count;
    if ((count != 0) && (malloc_size / count != size))
        return (NULL);

    if ((ptr = malloc(malloc_size)) != NULL)
        ft_bzero(ptr, malloc_size);
    return (ptr);
}
