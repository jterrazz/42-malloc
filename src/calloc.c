/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 14:42:17 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/20 22:57:16 by jterrazz         ###   ########.fr       */
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

    // show_alloc_mem();

    pthread_mutex_lock(&g_ft_malloc_mutex);
    // ft_putstr("Calloc/n");
    log_call(CALLOC);

    malloc_size = size * count;
    if ((count != 0) && (malloc_size / count != size)) { //wtf
        pthread_mutex_unlock(&g_ft_malloc_mutex);
        return (NULL);
    }

    pthread_mutex_unlock(&g_ft_malloc_mutex);

    if ((ptr = malloc(malloc_size))) {
        // tmp
        pthread_mutex_lock(&g_ft_malloc_mutex);
        ft_bzero(ptr, malloc_size);
        pthread_mutex_unlock(&g_ft_malloc_mutex);
    }

    return (ptr);
}
