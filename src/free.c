/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 19:08:52 by jterrazz          #+#    #+#             */
/*   Updated: 2019/04/17 19:02:18 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_range *get_range_of_block(t_range *range, t_block *block_searched) {
  t_block *block = NULL;

  while (range) {
    block = (t_block *) SHIFT_BLOCK(range);
    while (block) {
      if (block == block_searched) {
        return range;
      }
      block = block->next;
    }
    range = range->next;
  }
  return NULL;
}

void free(void *ptr) {
  t_range *range = get_default_range();
  t_block *block = (t_block *) REVERSE_SHIFT_BLOCK(ptr); // TODO Not sure, compare the segfaults

  if (!ptr)
    return;
  range = get_range_of_block(range, block);
  // if (!range)
  //   return;
  // block->freed = TRUE;
  // if (block->next == NULL) {
  //   block->prev->next = NULL;
  //   range->block_count--;
  //   // Go back in space and remove all lasts freed blocks
  // }
  // Unmap if no more blocks
}
