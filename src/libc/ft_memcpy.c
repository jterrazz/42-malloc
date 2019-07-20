/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 16:48:25 by jterrazz          #+#    #+#             */
/*   Updated: 2019/04/25 15:01:28 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void    *ft_memcpy(void *dst, const void *src, size_t n)
{
	char            *dst_str;
	char            *src_str;

	dst_str = (char *)dst;
	src_str = (char *)src;
	if (dst == src)
		return (dst);
	while (n--)
		*dst_str++ = *src_str++;
	return (dst);
}
