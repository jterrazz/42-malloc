/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   range.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 16:06:12 by jterrazz          #+#    #+#             */
/*   Updated: 2019/04/09 19:10:16 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_range *find_range_in_list(const t_range *list_start, const t_range_group group, const size_t required_size) {
  t_range *range_el = (t_range *) list_start;

  while (range_el) {
    if (range_el->group == group && range_el->free_size >= required_size)
      return range_el;
    range_el = range_el->next;
  }
  // Check for group then check the free space (do a test in separate files)
  return NULL;
}

static t_range *new_range(t_range_group group, size_t block_size) {
  const size_t allocation = get_range_allocation_from_block_size(block_size);

  t_range *range = (t_range *)mmap(NULL, range_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);

  range->prev = NULL;
  range->next = NULL;
  range->group = group;
  range->total_size = allocation; // Get the group size
  range->free_size = allocation - sizeof(t_range); // Check that

  printf("Created a new range: ");
  printf("total size %d // free size %d\n", (int)range->total_size, (int)range->free_size);

  return range;
}

t_range *get_range_with_free_size(const size_t size) { // Think about sizeof(struct)
  const t_range *default_range = *get_default_range();
  const t_range_group range_group = block_size_to_range_group(size);
  t_range *available_range;

  available_range = find_range_in_list(default_range, range_group, size);
  printf("Found this avaiable range: %p\n", available_range);
  if (available_range == NULL) {
    available_range = new_range(range_group, size);
    available_range->next = (t_range *) default_range;
    *get_default_range() = available_range;
  }

  return (t_range *)available_range;
}
