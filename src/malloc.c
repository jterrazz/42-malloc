/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 14:20:08 by jterrazz          #+#    #+#             */
/*   Updated: 2019/04/09 18:39:18 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Check all includes and forbidden fts
// Make graph to show how memory behave

#include "malloc.h"

// static void init_
// static void insert_empty_block_in_range(t_range range, t_block block) {
  // Iterate in the range to find the last block
  // return ;
// }

void *malloc(size_t size) {
  t_range *range = get_range_with_free_size((const size_t)size);
  // insert_empty_block_in_range(range, size);

  // 1st Search if mapped zone exists
  // -> Map if not
  // -> Create struct
  // Send back pointer
  return NULL;
}

int main(int argc, char const *argv[]) {
  void *test = malloc(129);
  void *test2 = malloc(129);
  void *test3 = malloc(129);
  void *test4 = malloc(129);
}
