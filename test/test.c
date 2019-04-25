/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 11:28:38 by jterrazz          #+#    #+#             */
/*   Updated: 2019/04/25 16:51:55 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Free need to decrease the range count
#include "test.h"
#include "malloc.h"

static void show_range_list() {
	t_range *range = get_default_range();
	// t_block *block =

	printf("RANGE LIST\n");

	int i = 0;
	while (range) {
		printf(
			"%d. Range %p, prev: %p, next: %p (count: %zu, group: %d, total size: %zu, free_space: %zu)\n",i, range, range->prev, range->next, range->block_count, range->group, range->total_size,
			range->free_size);
		range = range->next;
		i++;
	}
}

// Merging the two firsts
static void test_free_1(void) {
	show_alloc_mem();
	show_range_list();
	void *test = malloc(10);
	show_alloc_mem();
	show_range_list();
	void *test2 = malloc(10);
	show_alloc_mem();
	show_range_list();
	void *test3 = malloc(10);
	show_alloc_mem();
	show_range_list();
	free(test);
	free(test2);
	show_alloc_mem();
	show_range_list();
	free(test3);
}

static void test_free_2(void) {
	void *test = malloc(10);
	void *test2 = malloc(10);
	void *test3 = malloc(10);

	free(test);
	test2 = realloc(test2, 10);
	show_alloc_mem();
	test2 = realloc(test2, 11);
	show_alloc_mem();
	test2 = realloc(test2, 9); // TODO Error in data_size
	show_alloc_mem();
	show_range_list();
}

static void test_realloc_1(void) {
	show_alloc_mem();
	show_range_list();
	void *test = malloc(10);
	show_alloc_mem();
	show_range_list();
	test = realloc(test, 11);
	show_alloc_mem();
	show_range_list();
	test = realloc(test, 9);
	show_alloc_mem();
	show_range_list();
}

static void test_free_3(void) {
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
	// show_range_list();
	// free(NULL);
	// show_range_list();
	// free(test);
	// show_range_list();
	// free(test2);
	// show_range_list();
	// free(test5);
	// show_range_list();
	// free(test6);
	// show_range_list();
	// free(test3);
	// show_range_list();
	// free(test4);
	// show_range_list();
}

void test_show_alloc_mem_ex(void) {
	char *test = (char*) malloc(20);
	char *test2 = (char*) malloc(2000);
	test[0] = 5;
	test[1] = 5;
	test[2] = 5;
	test[3] = 5;
	test[4] = 5;
	test[5] = 5;
	show_alloc_meme_ex();
	free(test);
	free(test2);
}

// TODO Test with leaks !!!
// Check norminette on project
// Check the total size allocated is what expected

// TODO explain how to inject in lib
// Realloc test on + 5 address
// Print and verify all struct variables (like data_size total_size)
int main(int argc, char const *argv[]) {
	// Replace by my libs
	// run_realloc_tests();
	// test_blyat();
	// test_show_alloc_mem_ex();
	// test_free_1();
	// test_free_2();
	// test_free_3();
	// test_realloc_1();


	// void *test7 = malloc(129);
	// free(test7);

	// Test filling a merged memory merging
	// Also test with precise structure size
	// void *test10 = malloc(120);
	// void *test11 = malloc(120);
	// void *test12 = malloc(120);
	// void *test13 = malloc(120);
	// show_alloc_mem();
	// free(test11);
	// free(test12);
	// show_alloc_mem();
	// void *test_use_freed = malloc(150);
	// show_alloc_mem();
	// test10 = realloc(test10, 300);
	// void *test15 = malloc(20);
	//
	// test_use_freed = realloc(test_use_freed, 150);
	// show_alloc_mem();
	// test_use_freed = realloc(test_use_freed, 151);
	// free(test_use_freed);

	// TODO Check all memory is unmaped

	// show_alloc_mem();
	// show_range_list();
}

// TODO On the readme show an integration by replacing free of the system with things like ls / ls -l / etc

// Check if we dont reallocate or insert using search in the others types (SMALL TINY ETC) => for malloc and realloc

// TODO use getrlimit ???

// TODO Remove all printf
// TOOD Check is using a range until the end

// TESTS Tinies goes in tiny even with freed blocks in SMALL => MALLOC + REALLOC

// TODO Get tests for all githubs
