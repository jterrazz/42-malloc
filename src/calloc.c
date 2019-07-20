/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 14:42:17 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/20 15:20:45 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h> //rem

//just that
// if (!num || !nsize)
// 		return (NULL);
// 	size = num * nsize;
// 	if (nsize != size / num)
// 		return (NULL);

void*calloc(size_t count, size_t size)
{
    size_t malloc_size;
	void *ptr;

    // ft_putstr("Calloc/n");
    // show_alloc_mem();

    pthread_mutex_lock(&g_ft_malloc_mutex);
    log_call(CALLOC);

    malloc_size = size * count;
    if ((count != 0) && (malloc_size / count != size)) { //wtf
        pthread_mutex_unlock(&g_ft_malloc_mutex);
        return (NULL);
    }

    pthread_mutex_unlock(&g_ft_malloc_mutex);

    if ((ptr = malloc(malloc_size)))
        ft_bzero(ptr, malloc_size);

    return (ptr);
}
