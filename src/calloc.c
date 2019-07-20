/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 14:42:17 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/20 07:38:56 by jterrazz         ###   ########.fr       */
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
    // ft_putstr("Start function calloc\n");
    size_t malloc_size;
	void *ptr;

    pthread_mutex_lock(&g_ft_malloc_mutex);
    log_call(CALLOC);

    malloc_size = size * count;
    if ((count != 0) && (malloc_size / count != size)) { //wtf
        pthread_mutex_unlock(&g_ft_malloc_mutex);
        return (NULL);
    }

    pthread_mutex_unlock(&g_ft_malloc_mutex);

    //tmp
    // if (malloc_size < 400)
    //     return calloc(1, 400);

    // if (malloc_size % 16)
    //     return calloc(1, size + 16 - size % 16);

    if ((ptr = malloc(malloc_size)))
        ft_bzero(ptr, malloc_size);

    // ft_putstr("End function\n");
    return (ptr);
}
