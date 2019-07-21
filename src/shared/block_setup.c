/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 11:25:17 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/21 11:25:40 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void setup_block(t_block *block, size_t size)
{
	block->prev = NULL;
	block->next = NULL;
	block->data_size = size;
	block->freed = FALSE;
}
