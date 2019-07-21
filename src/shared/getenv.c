/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 09:44:13 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/21 15:14:29 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** We cache the environment variables in the first call
** https://github.com/xianyi/OpenBLAS/issues/716
*/

t_bool getenv_cached(t_env env)
{
    static uint32_t	env_cache;
    static t_bool	init;

    if (!init) {
        if (getenv("MyMallocStackLogging")) env_cache |= ENV_STACK_LOGGING;
        if (getenv("MyMallocFullLogging")) env_cache |= ENV_FULL_LOGGING;
        if (getenv("MyMallocScribble")) env_cache |= ENV_SCRIBBLE;
        init = TRUE;
    }

    return (env & env_cache);
}
