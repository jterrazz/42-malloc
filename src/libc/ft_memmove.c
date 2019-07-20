/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 18:26:16 by jterrazz          #+#    #+#             */
/*   Updated: 2019/04/25 15:01:25 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char			*dst_str;
	char			*src_str;

	dst_str = (char *)dst;
	src_str = (char *)src;
	if (dst == src)
		return (dst);
	if (dst_str < src_str)
		ft_memcpy(dst_str, src_str, len);
	else
	{
		while (len--)
			dst_str[len] = src_str[len];
	}
	return (dst);
}
