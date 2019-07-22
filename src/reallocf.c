/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallocf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 15:57:54 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/22 10:42:33 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** The reallocf() function changes the size of the previously allocated memory
** referenced by ptr to size bytes. The contents of the memory are unchanged
** up to the lesser of the new and old sizes
*/

void*start_reallocf(void *ptr, size_t size)
{
	void *res;

	res = start_realloc(ptr, size);
	if (!res && (size > 0))
		start_free(ptr);
	return (res);
}

void*reallocf(void *ptr, size_t size)
{
	void *res;

	pthread_mutex_lock(&g_ft_malloc_mutex);
	log_detail(REALLOCF);
	res = start_reallocf(ptr, size);
	pthread_mutex_unlock(&g_ft_malloc_mutex);
	return (res);
}
