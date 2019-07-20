/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_logs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 17:56:30 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/20 07:41:07 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <fcntl.h>
#include <unistd.h>

/*
getenv problem
https://github.com/xianyi/OpenBLAS/issues/716
*/

// static void log_allocation(int fd, size_t arg1, size_t arg2)
// {
// 	ft_itoa_fd(arg1, 10, fd, TRUE);
// 	write(fd, " - Allocation of ", 17);
// 	ft_itoa_fd(arg2, 10, fd, FALSE);
// 	write(fd, "\n", 1);
// }
//
// static void log_deallocation(int fd, size_t arg1)
// {
// 	if (arg1) {
// 		ft_itoa_fd(arg1, 10, fd, TRUE);
// 	} else {
// 		write(fd, "NULL", 4);
// 	}
// 	write(fd, " - Deallocation", 15);
// 	write(fd, "\n", 1);
// }

// rename run.sh

// bool ft_getenv(t_enviroment_opt env) {

// }
// Do a common function for both
bool_bef LoggingOn = B_NULL;
void log_call(t_call_event event)
{
	(void)event;
	// int fd;
	//
	// if (LoggingOn == B_NULL)
	// 	LoggingOn = !!getenv("MyMallocStackLogging") ? B_TRUE : B_FALSE;
	// if (LoggingOn == B_TRUE) {
	// 	if ((fd = open("/tmp/malloc.log", O_CREAT | O_WRONLY | O_APPEND, 0644)) == -1)
	// 		return;
	// 	if (event == MALLOC) {
	// 		write(fd, "Malloc called\n", 14);
	// 	} else if (event == CALLOC) {
	// 		write(fd, "Calloc called\n", 14);
	// 	} else if (event == FREE) {
	// 		write(fd, "Free called\n", 12);
	// 	} else if (event == REALLOC) {
	// 		write(fd, "Realloc called\n", 15);
	// 	} else {
	// 		write(fd, "Reallocf called\n", 16);
	// 	}
	// 	close(fd);
	// }
}

void log_stack(t_memory_event event, size_t arg1, size_t arg2)
{
	(void)event;
	(void)arg1;
	(void)arg2;
	// int fd;
	//
	// if (getenv("MyMallocStackLogging")) {
	// 	if ((fd = open("/tmp/malloc.log", O_CREAT | O_WRONLY | O_APPEND, 0644)) == -1)
	// 		return;
	// 	if (event == ALLOCATE) {
	// 		log_allocation(fd, arg1, arg2);
	// 	} else {
	// 		log_deallocation(fd, arg1);
	// 	}
	// 	close(fd);
	// }
}
