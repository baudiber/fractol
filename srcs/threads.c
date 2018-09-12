/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 15:22:02 by baudiber          #+#    #+#             */
/*   Updated: 2018/09/12 15:22:04 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		find_thread(t_setup *stp)
{
	pthread_t	tid;
	int			i;

	tid = pthread_self();
	i = -1;
	while (++i < MAX_THREADS)
	{
		if (pthread_equal(stp->tids[i], tid))
			break ;
	}
	return (i);
}
