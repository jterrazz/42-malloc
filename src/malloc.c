/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 14:20:08 by jterrazz          #+#    #+#             */
/*   Updated: 2019/04/17 16:44:02 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Check all includes and forbidden fts
// Make graph to show how memory behave
// Handle malloc errors

#include "malloc.h"

static t_block *get_last_block_item(t_block *block) {
  while (block->next) {
    block = block->next;
  }

  return block;
}

static void insert_empty_block(t_block *block, size_t size) {
  block->prev = NULL;
  block->next = NULL;
  block->data_size = size;
  block->freed = FALSE;
}

static void append_empty_block(t_range *range, size_t size) {
  t_block *current_block = (t_block *) SHIFT_RANGE(range);
  t_block *last_block = NULL;

  if (range->block_count) {
    last_block = get_last_block_item(current_block);
    current_block = (t_block *) SHIFT_BLOCK(last_block);
  }
  insert_empty_block(current_block, size);
  if (range->block_count) {
    last_block->next = current_block;
    current_block->prev = last_block;
  }
  range->block_count++;
  range->free_size = range->free_size - current_block->data_size - sizeof(t_block);
}

void *malloc(size_t size) {
  t_range *range = get_range_of_block_size((const size_t)size);
  if (!range)
    return NULL;
  append_empty_block(range, size);

  printf("Free size is %d\n", range->free_size);

  // 1st Search if mapped zone exists
  // -> Map if not3
  // -> Create struct
  // Send back pointer
  return NULL;
}

// Free need to decrease the range count
int main(int argc, char const *argv[]) {
  void *test = malloc(129);
  void *test2 = malloc(129);
  void *test3 = malloc(12900);
  void *test4 = malloc(129);
  malloc(1);
  malloc(0);

  show_alloc_mem();
}

// TODO Remove all printf
