/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   range.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 16:06:12 by jterrazz          #+#    #+#             */
/*   Updated: 2019/05/31 20:11:55 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <sys/resource.h>
#include "malloc.h"

t_range*get_last_range(t_range *range)
{
    if (!range)
        return (NULL);

    while (range->next) {
        range = range->next;
    }

    return (range);
}

static t_range*find_available_range(const t_range *list_start,
    const t_range_group group,
    const size_t required_size)
{
    t_range *range_el = (t_range *)list_start;

    while (range_el) {
        if ((range_el->group == group) &&
            (range_el->free_size >= required_size))
            return (range_el);

        range_el = range_el->next;
    }
    return (NULL);
}

static rlim_t get_system_limit() {
    struct rlimit rpl;

    if (getrlimit(RLIMIT_DATA, &rpl) < 0)
        return (-1);

    return rpl.rlim_max;
}

static t_range*new_range(t_range_group group, size_t block_size)
{
    size_t	range_size;
    t_range	*range;

    range_size = get_range_size_from_block_size(block_size);
    if (range_size > get_system_limit())
        return (NULL);

    range = (t_range *)mmap(NULL, range_size,
        PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);

    if (range == MAP_FAILED)
        return (NULL);

    range->prev		= NULL;
    range->next		= NULL;
    range->group		= group;
    range->block_count	= 0;
    range->total_size	= range_size;
    range->free_size	= range_size - sizeof(t_range);

    return (range);
}

t_range*get_range_of_block_size(const size_t size)
{
    t_range		*default_range;
    t_range_group	range_group;
    t_range		*range;

    default_range	= get_default_range();
    range_group		= get_range_group_from_block_size(size);
    range		= find_available_range(default_range,
        range_group,
        size + sizeof(t_block));

    if (range == NULL) {
        if (!(range = new_range(range_group, size)))
            return (NULL);

        range->next = (t_range *)default_range;
        if (range->next) {
            range->next->prev = range;
        }
        set_default_range(range);
    }

    return ((t_range *)range);
}
