/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 15:31:32 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/21 15:10:40 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void    ft_itoa_fd(size_t nb, char base, int fd, t_bool prefix)
{
    char *str;

    str = "0123456789ABCDEFGHIJKLMNOPQRSTUIVWXYZ";
    if (nb / base != 0)
        ft_itoa_fd(nb / base, base, fd, prefix);
    else {
        if (prefix)
            write(fd, "0x", 2);
    }
    write(fd, &str[nb % base], 1);
}

void    ft_itoa_base(size_t nb, char base, char length, t_bool prefix)
{
    char *str;

    str = "0123456789ABCDEFGHIJKLMNOPQRSTUIVWXYZ";
    if (nb / base != 0)
        ft_itoa_base(nb / base, base, --length, prefix);
    else {
        if (prefix)
            ft_putstr("0x");
        while (--length > 0) {
            ft_putstr("0");
        }
    }
    write(1, &str[nb % base], 1);
}
