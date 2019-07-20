/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 14:42:17 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/20 23:41:06 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
    Calloc returns a memory zone set to zero
    Returns null for count = 0, size = 0 or if overflow of their multiplication
*/

void *start_calloc(size_t count, size_t size)
{
    size_t total_size;
	void *res;

    total_size = size * count;
    if (!count || !size || (total_size / count != size))
        return (NULL);

    if ((res = start_malloc(total_size)))
        ft_bzero(res, total_size);

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
