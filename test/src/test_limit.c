/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_limit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 20:09:51 by jterrazz          #+#    #+#             */
/*   Updated: 2019/05/31 20:13:20 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./test.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>

void run_test_rlimit()
{
    char *t;
    struct rlimit rpl;

    rpl.rlim_cur = TINY_HEAP_ALLOCATION_SIZE;
    rpl.rlim_max = TINY_HEAP_ALLOCATION_SIZE;

    if (setrlimit(RLIMIT_DATA, &rpl) < 0)
        printf("setrlimit did not work\n");

    if (!(t = (char *)malloc(TINY_HEAP_ALLOCATION_SIZE - sizeof(t_block) - sizeof(t_heap))))
        printf("malloc() should return ptr\n");
    free(t);

    if ((t = (char *)malloc(TINY_HEAP_ALLOCATION_SIZE)))
        printf("malloc() should return NULL\n");
    free(t);
}
