/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 14:42:17 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/22 10:41:28 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** The calloc() function allocates memory for an array of nmemb elements of size
** bytes each and returns a pointer to the allocated memory. The memory is set
** to zero. If nmemb or size is 0, then calloc() returns either NULL, or a
** unique pointer value that can later be successfully passed to free().
*/

void*start_calloc(size_t count, size_t size)
{
	size_t	total_size;
	void	*res;

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
	log_detail(CALLOC);
	res = start_calloc(count, size);
	pthread_mutex_unlock(&g_ft_malloc_mutex);
	return (res);
}
