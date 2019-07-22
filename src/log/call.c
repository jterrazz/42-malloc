/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 17:56:30 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/22 10:44:54 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	log_allocation(int fd, size_t size)
{
	ft_putstr_fd(" allocated ", fd);
	ft_itoa_fd(size, 10, fd, FALSE);
	ft_putstr_fd(" bytes\n", fd);
}

static void	log_deallocation(int fd, size_t size)
{
	ft_putstr_fd("Released \n", fd);
	ft_itoa_fd(size, 10, fd, TRUE);
	ft_putstr_fd(" bytes\n", fd);
}

void		log_stack(t_stack_event event, size_t size)
{
	int fd;

	if (getenv_cached(ENV_STACK_LOGGING) || getenv_cached(ENV_FULL_LOGGING))
	{
		if ((fd = open(LOGS_PATH, O_CREAT | O_WRONLY | O_APPEND, 0644)) == -1)
			return ;
		if (event == ALLOCATE)
			log_allocation(fd, size);
		else
			log_deallocation(fd, size);
		close(fd);
	}
}

void		log_detail(t_detail_event event)
{
	int fd;

	if (getenv_cached(ENV_FULL_LOGGING))
	{
		if ((fd = open(LOGS_PATH, O_CREAT | O_WRONLY | O_APPEND, 0644)) == -1)
			return ;
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
