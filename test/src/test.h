/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 15:17:19 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/21 15:17:20 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_TEST
#define MALLOC_TEST

#include "malloc.h"

#define M1 (1024 * 1024)

void run_test_malloc(void);
void run_test_realloc(void);
void run_test_mixed(void);
void show_heap_list();
void run_test_rlimit();

#endif
