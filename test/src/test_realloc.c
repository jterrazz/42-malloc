/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_realloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 18:47:22 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/22 11:56:18 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "./test.h"

static void realloc_null_ptr() {
	char *t = realloc(NULL, 5);

	if (!t)
		printf("Realloc(NULL, 5) should return ptr");
	free(t);
}

static void realloc_0() {
	char *t = malloc(4);
	t = realloc(t, 0);

	if (t)
		printf("Realloc(ptr, 0) should return NULL");
	free(t);
}

static void realloc_1() {
	char *t = malloc(1);
	t = realloc(t, 1);
	t = realloc(t, 10);
	t[0] = 'A';
	t[9] = 'A';
	t = realloc(t, TINY_BLOCK_SIZE);
	t = realloc(t, SMALL_BLOCK_SIZE);
	t = realloc(t, SMALL_BLOCK_SIZE + 2);
	t = realloc(t, 10);

	if (t[0] != 'A' || t[9] != 'A')
		printf("Realloc should copy data");
	free(t);
}

static void realloc_large()
{
	char    *addr1;
	char    *addr2;
	char    *addr3;

	addr1 = (char *)malloc(1 * M1);
	// strcpy(addr1, "Bonjours\n");
	// addr2 = (char *)malloc(16 * M1);
	// addr3 = (char *)realloc(addr1, 128* M1);
	// addr3[127 * M1] = 42;
	// free(addr3);
	// free(addr2);
	// free(addr1);
}

void run_test_realloc(void)
{
	realloc_null_ptr();
	realloc_0();
	realloc_1();
	realloc_large();
}
