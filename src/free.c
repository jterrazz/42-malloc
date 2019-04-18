/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 19:08:52 by jterrazz          #+#    #+#             */
/*   Updated: 2019/04/18 18:38:36 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void convert_ptr(t_range **found_range, t_block **found_block, t_range *range, void *ptr) {
  t_block *block = NULL;

  while (range) {
    block = (t_block *)SHIFT_RANGE(range);
    printf("Searching range : %p\n", range);
    while (block) {
        printf("Searching block : %p compared to %p of size %d\n", ptr, SHIFT_BLOCK(block), block->data_size);
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

void merge_near_freed_blocks(t_range *range, t_block *block) {
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
    if (!range->block_count) {
        munmap(range, range->total_size);
    }
}

void free(void *ptr) {
  t_range *range = get_default_range();
  t_block *block = NULL; // TODO Not sure, compare the segfaults

  printf("CALLING FREE\n");

  if (!ptr || !range)
    return;

  convert_ptr(&range, &block, range, ptr);
  printf("Pointer 1 : %p\n", range);
  printf("Pointer 2 : %p\n", block);

  if (block && range) {
      block->freed = TRUE;
      // Clean if in the last blocks // maybe merge if next to others freed
      merge_near_freed_blocks(range, block);
      remove_if_last_block(range, block);
      //   block->prev->next = NULL;
      //   range->block_count--;
  }
  unmap_if_empty(range);
}
// Test the merging is working


// use getrlimit()
