/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 11:28:38 by jterrazz          #+#    #+#             */
/*   Updated: 2019/05/31 18:31:41 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "./test.h"

// TODO use getrlimit + setrlimit
// TODO Remove all printf

int main(void) {
	run_test_malloc();
	// run_test_mixed();
}
