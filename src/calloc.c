/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 14:42:17 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/11 15:16:08 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void*calloc(size_t count, size_t size)
{
    size_t malloc_size;
	void *ptr;

    pthread_mutex_lock(&g_ft_malloc_mutex);

    malloc_size = size * count;
    if ((count != 0) && (malloc_size / count != size)) {
        pthread_mutex_unlock(&g_ft_malloc_mutex);
        return (NULL);
    }

    pthread_mutex_unlock(&g_ft_malloc_mutex);
    if ((ptr = malloc(malloc_size)) != NULL)
        ft_bzero(ptr, malloc_size);

    return (ptr);
}
