/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 11:28:38 by jterrazz          #+#    #+#             */
/*   Updated: 2019/04/20 18:46:53 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Free need to decrease the range count
#include "malloc.h"

static void print_default_range_list() {
	t_range *range = get_default_range();
	// t_block *block =

	printf("RANGE LIST\n");

	int i = 0;
    while (range) {
        printf("%d. Range %p, prev: %p, next: %p (count: %zu, group: %d, total size: %zu)\n",i , range, range->prev, range->next, range->block_count, range->group, range->total_size);
        range = range->next;
		i++;
    }
}

int main(int argc, char const *argv[]) {
	// void *test = malloc(10);
	// test = "1234567890"; // TODO Do with while
	// void *test2 = malloc(129);
	// void *test3 = malloc(12900); // Add security for value max (with function to get max memory of system)
	// void *test4 = malloc(129);
	// void *test5 = malloc(1);
	// void *test6 = malloc(0);
	//
	// test2 = realloc(test2, 1200);
	//
	// print_default_range_list();
	// free(NULL);
	// print_default_range_list();
	// free(test);
	// print_default_range_list();
	// free(test2);
	// print_default_range_list();
	// free(test5);
	// print_default_range_list();
	// free(test6);
	// print_default_range_list();
	// free(test3);
	// print_default_range_list();
	// free(test4);
	// print_default_range_list();

	void *test7 = malloc(129);
	free(test7);

	// Test filling a merged memory merging
	// Also test with precise structure size
	void *test10 = malloc(120);
	void *test11 = malloc(120);
	void *test12 = malloc(120);
	void *test13 = malloc(120);
	show_alloc_mem();
	free(test11);
	free(test12);
	show_alloc_mem();
	void *test_use_freed = malloc(150);
	show_alloc_mem();
	test10 = realloc(test10, 300);
	void *test15 = malloc(20);

	test_use_freed = realloc(test_use_freed, 150);
	show_alloc_mem();
	test_use_freed = realloc(test_use_freed, 151);
	// free(test_use_freed);

	// TODO Check all memory is unmaped

	show_alloc_mem();
	print_default_range_list();
}

// Check if we dont reallocate or insert using search in the others types (SMALL TINY ETC) => for malloc and realloc

// TODO use getrlimit ???

// TODO Remove all printf
// TOOD Check is using a range until the end

// TESTS Tinies goes in tiny even with freed blocks in SMALL => MALLOC + REALLOC
