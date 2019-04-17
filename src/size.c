/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 17:13:09 by jterrazz          #+#    #+#             */
/*   Updated: 2019/04/17 14:58:51 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_range_group get_range_group_from_block_size(size_t size) {
  if (size <= TINY_BLOCK_SIZE) { // Check is not <= // Check is comapred with struct data space
    return TINY;
  } else if (size <= SMALL_BLOCK_SIZE) {
    return SMALL;
  }

  return LARGE;
}

// size_t range_group_to_total_size(t_range_group range_group, size_t large_size) {
//   if (range_group == TINY) {
//     return TINY_RANGE_ALLOCATION;
//   } else if (range_group == SMALL) {
//     return SMALL_RANGE_ALLOCATION;
//   } else {
//     return large_size + sizeof(t_range) + sizeof(t_block); // not sure make a test for that
//   }
// }

size_t get_range_allocation_from_block_size(size_t size) {
  t_range_group range_group = get_range_group_from_block_size(size);

  if (range_group == TINY) {
    return TINY_RANGE_ALLOCATION_SIZE;
  } else if (range_group == SMALL) {
    return SMALL_RANGE_ALLOCATION_SIZE;
  }

  return size + sizeof(t_range) + sizeof(t_block); // +1 ?
}
