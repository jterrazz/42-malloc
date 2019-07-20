/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallocf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 15:57:54 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/20 15:20:57 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void *reallocf(void *ptr, size_t size)
{
	// ft_putstr("Start function reallocf\n");
	void *ret;

	// ft_putstr("Reallocf/n");
	// show_alloc_mem();
	log_call(REALLOCF);
	ret = realloc(ptr, size);
	if (!ret && size > 0)
		free(ptr);

	// ft_putstr("End function\n");
	return (ret);
}
