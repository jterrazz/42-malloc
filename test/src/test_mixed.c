/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_mixed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 18:47:10 by jterrazz          #+#    #+#             */
/*   Updated: 2019/05/31 18:29:24 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "./test.h"

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

void run_test_mixed(void)
{
    printf("OK\n");
	test_free_1();
	// test_blyat();
	// test_show_alloc_mem_ex();
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
