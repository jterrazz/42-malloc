/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 15:31:32 by jterrazz          #+#    #+#             */
/*   Updated: 2019/05/04 01:43:29 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void    ft_itoa_base(size_t nb, char base, char length)
{
	char    *str;

	str = "0123456789abcdefghijklmnopqrstuvwxyz";
	if (nb / base != 0)
		ft_itoa_base(nb / base, base, --length);
	else {
		while (--length > 0) {
			ft_putstr("0");
		}
	}
	write(1, &str[nb % base], 1);
	return;
}
