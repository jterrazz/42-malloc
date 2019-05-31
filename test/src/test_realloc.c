/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_realloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 18:47:22 by jterrazz          #+#    #+#             */
/*   Updated: 2019/05/31 18:32:32 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Realloc de NULL
// Realloc de 0
// realloc de 0 et de 1
// Realloc from LARGE to TINY
// Realloc from SMALL to TINY
// Realloc from SMALL to LARGE etc

#include <stdio.h>
#include "./test.h"

static void test_1()
{
	char    *addr1;
	char    *addr2;
	char    *addr3;

	addr1 = (char *)malloc(1 * M1);
	strcpy(addr1, "Bonjours\n");
	printf(addr1);
	addr2 = (char *)malloc(16 * M1);
	addr3 = (char *)realloc(addr1, 128* M1);
	addr3[127 * M1] = 42;
	printf(addr3);
	show_alloc_mem();
	free(addr3);
	free(addr2);
	free(addr1);
}

void run_test_realloc(void)
{
    printf("Running malloc tests\n");
    test_1();
}
