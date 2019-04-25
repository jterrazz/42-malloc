/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   range_default.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 19:06:00 by jterrazz          #+#    #+#             */
/*   Updated: 2019/04/25 15:00:37 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_range **default_range(void) {
	static t_range *default_range = NULL;

	return (&default_range);
}

t_range *get_default_range(void) {
	return *default_range();
}

void set_default_range(t_range *range) {
	*default_range() = range;
}
