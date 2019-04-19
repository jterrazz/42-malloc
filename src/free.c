/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 19:08:52 by jterrazz          #+#    #+#             */
/*   Updated: 2019/04/19 17:44:20 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void convert_ptr(t_range **found_range, t_block **found_block, t_range *range, void *ptr) {
  t_block *block = NULL;

  while (range) {
    block = (t_block *)SHIFT_RANGE(range);
    while (block) {
      if ((void *) SHIFT_BLOCK(block) == ptr) {
        *found_range = range;
        *found_block = block;
        return;
      }
      block = block->next;
    }
    range = range->next;
  }
}

// Explain why we merge in readme => so we use the freed space more efficiently (bonus defrag)
void merge_near_freed_blocks(t_range *range, t_block *block) { // check if doesnt make problem with sizes
    if (block->prev && block->prev->freed) {
        block->prev->next = block->next;
        block->prev->data_size += block->data_size + sizeof(t_block);
        range->block_count--;
        merge_near_freed_blocks(range, block->prev);
    } else if (block->next && block->next->freed) {
        block->next->prev = block->prev;
        block->next->data_size += block->data_size + sizeof(t_block);
        range->block_count--;
        merge_near_freed_blocks(range, block->next);
    }
}

void remove_if_last_block(t_range *range, t_block *block) {
    if (block->freed && !block->next && block->prev) {
        block->prev->next = NULL;
        range->free_size += block->data_size + sizeof(t_block);
    }
    // Add to free size
    range->block_count--;
}

void unmap_if_empty(t_range *range) {
    t_range *static_range = get_default_range();
    bool is_last = FALSE;
    size_t unmap_size = 0;

    if (range->prev) {
        range->prev->next = range->next;
    }
    if (range->next) {
        range->next->prev = range->prev;
    }
    if ((range == static_range) || (!range->next && !range->prev)) {
        if (!range->block_count)
            is_last = TRUE;
        unmap_size = range->total_size;
        set_default_range(range->next);
    }
    // if (is_last) {
    //     printf("HEllo4\n");
    //     munmap(range, unmap_size);
    // }
}

void print_range_list(t_range *range) {
    while (range) {
        printf("Range %p with group %d with total size: %zu (next: %p, prev: %p)\n", range, range->group, range->total_size, range->next, range->prev);
        range = range->next;
    }
}

void free(void *ptr) {
  t_range *range = get_default_range();
  t_block *block = NULL; // TODO Not sure, compare the segfaults

  print_range_list(range);

  if (!ptr || !range)
    return;

  convert_ptr(&range, &block, range, ptr);

  if (block && range) {
      block->freed = TRUE;
      // Clean if in the last blocks // maybe merge if next to others freed
      merge_near_freed_blocks(range, block);

      remove_if_last_block(range, block);
  }
  unmap_if_empty(range);
}
// Test the merging is working


// use getrlimit()
