/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 17:54:01 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/21 11:23:11 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block *get_last_block(t_block *block) {
	while (block->next) {
		block = block->next;
	}

	return block;
}
