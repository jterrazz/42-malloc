/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:06:42 by jterrazz          #+#    #+#             */
/*   Updated: 2019/04/19 17:39:40 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_range *get_last_range(t_range *range) {
  if (!range)
    return NULL;
  while (range->next) {
    range = range->next;
  }

  return range;
}

// TODO Check the printed size is real
// TODO Check a full sized malloc of the map is working
// TODO getPageSize()
// TODO Check address + int will make different value with cast in char* or no
// cast

static void print_block_list(t_block *block) {
  char *start_address = NULL;
  char *end_address = NULL;

  while (block) {
    start_address = (char *)SHIFT_BLOCK(block);
    end_address = start_address + block->data_size; // TODO -1 ????
    printf("%p - %p : %zu octets\n", start_address, end_address,
           block->data_size);
    block = block->next;
  }
}

void debug_range(t_range *range) {
    int i = 0;
    char *ptr = (char *) range;

    while (i < 40) {
        printf("%c", *(ptr + 1));
        i++;
    }
}

void show_alloc_mem() {
  t_range *first_range = get_default_range();
  t_range *last_range = get_last_range(first_range);

  // TODO Check it will always be in order (small to big address), in case mmap goes back
  while (last_range) {
    if (last_range->group == TINY) {
      printf("TINY : %p\n", last_range);
    } else if (last_range->group == SMALL) {
      printf("SMALL : %p\n", last_range);
    } else {
      printf("LARGE : %p\n", last_range);
    }
    // printf("=   -> Total size: %zu (free size: %zu)\n", last_range->total_size,
           // last_range->free_size);
    // printf("=   -> Contains %u blocks\n", last_range->block_count);

    if (last_range->block_count)
      print_block_list((t_block *)SHIFT_RANGE(last_range));

    // debug_range(last_range);

    last_range = last_range->prev;
  }
}
