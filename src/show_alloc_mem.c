/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:06:42 by jterrazz          #+#    #+#             */
/*   Updated: 2019/04/17 17:00:37 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_range *get_last_range(t_range *range) {
  while (range->next) {
    range = range->next;
  }

  return range;
}

void show_alloc_mem() {
  t_range *first_range = get_default_range();
  t_range *last_range = get_last_range(first_range);

  printf("==========================\n");
  printf("========== DEBUG =========\n");
  printf("==========================\n");
  while (last_range) {
    if (last_range->group == TINY) {
      printf("= TINY : %p\n", last_range);
    } else if (last_range->group == SMALL) {
      printf("= SMALL : %p\n", last_range);
    } else {
      printf("= LARGE : %p\n", last_range);
    }
    printf("=   -> Total size: %zu (free size: %zu)\n", last_range->total_size, last_range->free_size);
    printf("=   -> Contains %u blocks\n", last_range->block_count);
    last_range = last_range->prev;
  }
}
