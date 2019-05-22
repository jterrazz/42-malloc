/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_range.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 01:57:33 by jterrazz          #+#    #+#             */
/*   Updated: 2019/05/04 01:59:11 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void print_range_group(t_range *range) {
	if (range->group == TINY) {
		ft_putstr("TINY");
	} else if (range->group == SMALL) {
		ft_putstr("SMALL");
	} else {
		ft_putstr("LARGE");
	}
}

t_range *get_last_range(t_range *range) {
	if (!range)
		return NULL;
	while (range->next) {
		range = range->next;
	}

	return range;
}
