/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 09:44:13 by jterrazz          #+#    #+#             */
/*   Updated: 2019/07/21 09:45:30 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

bool getenv_cached(t_env env)
{
	static bool_bef StackLogging = B_NULL;
	static bool_bef FullLogging = B_NULL;
	static bool_bef Scribble = B_NULL;

	if (env == ENV_STACK_LOGGING)
		return (StackLogging = StackLogging || !!getenv("MyMallocStackLogging") ? B_TRUE : B_FALSE) == B_TRUE; // Not working apparently tes t all separate
	else if (env == ENV_FULL_LOGGING)
		return (FullLogging = FullLogging || !!getenv("MyMallocFullLogging") ? B_TRUE : B_FALSE) == B_TRUE;
	else if (env == ENV_SCRIBLE)
		return (Scribble = Scribble || !!getenv("MyMallocScribble") ? B_TRUE : B_FALSE) == B_TRUE;
	return (FALSE);
}
