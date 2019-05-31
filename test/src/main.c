/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 11:28:38 by jterrazz          #+#    #+#             */
/*   Updated: 2019/05/31 20:32:46 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "./test.h"

int main(void) {
	run_test_malloc();
	run_test_realloc();
	run_test_mixed();

	run_test_rlimit(); // Always at the end
}
