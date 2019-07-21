/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 17:56:30 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/21 14:24:19 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

// Check addresses are logged fully (No length ??? in ftitoa ????)
static void log_allocation(int fd, size_t arg1, size_t arg2)
{
	ft_itoa_fd(arg1, 10, fd, TRUE); // Address so 16 ???
	ft_putstr_fd(" allocated ", fd);
	ft_itoa_fd(arg2, 10, fd, FALSE);
	ft_putstr_fd(" bytes\n", fd);
}

static void log_deallocation(int fd, size_t arg1, size_t arg2)
{
	ft_itoa_fd(arg1, 10, fd, TRUE); // Address so 16 ???
	ft_putstr_fd(" released \n", fd);
	ft_itoa_fd(arg2, 10, fd, TRUE);
	ft_putstr_fd(" bytes\n", fd);
}

void log_stack(t_stack_event event, size_t arg1, size_t arg2)
{
	int fd;

	if (getenv_cached(ENV_STACK_LOGGING) || getenv_cached(ENV_FULL_LOGGING)) {
		if ((fd = open(LOGS_PATH, O_CREAT | O_WRONLY | O_APPEND, 0644)) == -1)
			return;
		if (event == ALLOCATE)
			log_allocation(fd, arg1, arg2);
		else
			log_deallocation(fd, arg1, arg2);
		close(fd);
	}
}

void log_detail(t_detail_event event)
{
	int fd;

	if (getenv_cached(ENV_FULL_LOGGING)) {
		if ((fd = open(LOGS_PATH, O_CREAT | O_WRONLY | O_APPEND, 0644)) == -1)
			return;
		if (event == MALLOC)
			ft_putstr_fd("Malloc call\n", fd);
		else if (event == CALLOC)
			ft_putstr_fd("Calloc call\n", fd);
		else if (event == FREE)
			ft_putstr_fd("Free call\n", fd);
		else if (event == REALLOC)
			ft_putstr_fd("Realloc call\n", fd);
		else if (event == REALLOCF)
			ft_putstr_fd("Reallocf call\n", fd);
		else if (event == HEAP_CREATE)
			ft_putstr_fd("Created a new heap\n", fd);
		else
			ft_putstr_fd("Deleted a heap\n", fd);
		close(fd);
	}
}
