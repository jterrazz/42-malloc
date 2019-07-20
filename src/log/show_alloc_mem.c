/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:06:42 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/20 17:53:50 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static size_t print_block_list(t_block *block, int fd)
{
    char	*start_address;
    char	*end_address;
    size_t	total;

    total		= 0;
    start_address	= NULL;
    end_address		= NULL;

    while (block) {
        start_address	= (char *)SHIFT_BLOCK(block);
        end_address	= start_address + block->data_size;

        if (!block->freed) {
            ft_itoa_base((size_t)start_address, 16, 9, TRUE);
            ft_putstr_fd(" - ", fd);
            ft_itoa_base((size_t)end_address, 16, 9, TRUE);
            ft_putstr_fd(" : ", fd);
            ft_itoa_base(block->data_size, 10, 0, FALSE);
            ft_putstr_fd(" octets ", fd); // \n
            total += block->data_size;
        } else {
            ft_putstr_fd("Freed block : ", fd);
            ft_itoa_base(block->data_size, 10, 0, FALSE);
            ft_putstr_fd(" octets ", fd); // \n
        }

        // Tmp
        ft_putstr_fd(" - Size should be for without block header ", fd);
        ft_itoa_base((void *)block->next - (void *) block - sizeof(t_block), 10, 0, FALSE);
        ft_putstr_fd(" - Next block ", fd);
        ft_itoa_base((size_t)block->next, 16, 9, TRUE);
        ft_putstr_fd("\n", fd);

        block = block->next;
    }
    return (total);
}

static void print_heap_header(char *name, t_heap *heap, int fd)
{
    ft_putstr_fd(name, fd);
    ft_putstr_fd(" : ", fd);
    ft_itoa_base((size_t)heap, 16, 9, TRUE);

    //tmp
    ft_putstr_fd(" (end: ", fd);
    ft_itoa_base((size_t)heap + heap->total_size, 16, 9, TRUE);
    ft_putstr_fd(")", fd);

    ft_putstr_fd("\n", fd);
}

// COmpare with expected result and add env var for complete debug
void show_alloc_mem()
{
    t_heap	*first_heap;
    t_heap	*last_heap;
    size_t	total;






    pthread_mutex_lock(&g_ft_malloc_mutex);




    int fd = 1;
        // if ((fd = open(LOGS_PATH, O_CREAT | O_WRONLY | O_APPEND, 0644)) == -1)
        //     return;




    total	= 0;
    first_heap = get_default_heap();
    last_heap	= get_last_heap(first_heap);

    while (last_heap) {
        if (last_heap->group == TINY) {
            print_heap_header("TINY", last_heap, fd);
        } else if (last_heap->group == SMALL) {
            print_heap_header("SMALL", last_heap, fd);
        } else {
            print_heap_header("LARGE", last_heap, fd);
        }

        if (last_heap->block_count)
            total += print_block_list((t_block *)SHIFT_HEAP(last_heap), fd);
        last_heap = last_heap->prev;
    }

    ft_putstr_fd("Total : ", fd);
    ft_itoa_base(total, 10, 0, FALSE);
    ft_putstr_fd(" octets\n", fd);
    ft_putstr_fd("\n", fd);



    // close(fd);



    pthread_mutex_unlock(&g_ft_malloc_mutex);
}
