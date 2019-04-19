/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 14:20:08 by jterrazz          #+#    #+#             */
/*   Updated: 2019/04/19 17:44:35 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Check all includes and forbidden fts
// Make graph to show how memory behave
// Handle malloc errors
// TODO Malloc de 0 et de 1 en test
// TODO Malloc negatif
// Size_t long ou int

#include "malloc.h"
// TODO Prevoir les int max overflows
// TODO Put in dedicated file
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

static void *append_empty_block(t_range *range, size_t size) {
  t_block *new_block = (t_block *)SHIFT_RANGE(range);
  t_block *last_block = NULL;

  if (range->block_count) {
    last_block = get_last_block_item(new_block);
    new_block =
        (t_block *)(SHIFT_BLOCK(last_block) + last_block->data_size); // TODO Check I dont need to cast to char
  }
  insert_empty_block(new_block, size);
  if (range->block_count) {
    last_block->next = new_block;
    new_block->prev = last_block;
  }
  range->block_count++;
  range->free_size =
      range->free_size - new_block->data_size - sizeof(t_block);
  return (void *) SHIFT_BLOCK(new_block);
}

void *malloc(size_t size) {
  if (!size)
    return NULL;
  t_range *range = get_range_of_block_size((const size_t)size);
  if (!range)
    return NULL;
  return append_empty_block(range, size); // Search if existing block can be added
}

void debug_values(char *ptr){
    // printf("\n%s\n\n\n", ptr);
}

// Free need to decrease the range count
int main(int argc, char const *argv[]) {
  void *test = malloc(10);
  // test = "1234567890"; // TODO Do with while
  void *test2 = malloc(129);
  void *test3 = malloc(12900);
  void *test4 = malloc(129);
  void *test5 = malloc(1);
  void *test6 = malloc(0);

  debug_values(test);

  free(NULL);
  free(test);
  free(test2);
  free(test5);
  free(test6);
  free(test3);
  free(test4);

  show_alloc_mem();
  void *test12 = malloc(129);
  free(test12);
  show_alloc_mem();
}

// TODO use getrlimit ???

// TODO Remove all printf
// TOOD Check is using a range until the end
