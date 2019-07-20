/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 14:42:17 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/20 23:36:04 by jterrazz         ###   ########.fr       */
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

void *start_calloc(size_t count, size_t size)
{
    size_t malloc_size;
	void *res;

    malloc_size = size * count;
    if ((count != 0) && (malloc_size / count != size))
        return (NULL);

    if ((res = start_malloc(malloc_size))) {
        ft_bzero(res, malloc_size);
    }

    return (res);
}

void*calloc(size_t count, size_t size)
{
    void *res;

    pthread_mutex_lock(&g_ft_malloc_mutex);
    log_call(CALLOC);
    res = start_calloc(count, size);
    pthread_mutex_unlock(&g_ft_malloc_mutex);

    return (res);
}
