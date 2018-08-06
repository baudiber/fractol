/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 19:34:14 by baudiber          #+#    #+#             */
/*   Updated: 2018/08/06 19:55:41 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	bship(t_xy xy, t_setup *stp, int tid)
{
	double	rsqr;
	double	isqr;
	int		i;

	stp->tmp[tid].z_r = 0;
	stp->tmp[tid].z_i = 0;
	stp->tmp[tid].c_r = xy.x / stp->tmp[tid].zoom + stp->tmp[tid].x1;
	stp->tmp[tid].c_i = xy.y / stp->tmp[tid].zoom + stp->tmp[tid].y1;
	rsqr = stp->tmp[tid].z_r * stp->tmp[tid].z_r;
	isqr = stp->tmp[tid].z_i * stp->tmp[tid].z_i;
	i = 0;
	while (rsqr + isqr < (1 << 16) && i < stp->tmp[tid].iteration_max)
	{
		stp->tmp[tid].tmp = rsqr - isqr + stp->tmp[tid].c_r;
		stp->tmp[tid].z_i = ABS(2 * stp->tmp[tid].z_r * stp->tmp[tid].z_i) \
			+ stp->tmp[tid].c_i;
		stp->tmp[tid].z_r = ABS(stp->tmp[tid].tmp);
		rsqr = SQR(stp->tmp[tid].z_r);
		isqr = SQR(stp->tmp[tid].z_i);
		i++;
	}
	set_pixel(i, stp, tid, &xy);
}

void	*draw_bship(void *arg)
{
	t_setup		*stp;
	t_xy		coord;
	int			i;
	pthread_t	tid;

	stp = (t_setup *)arg;
	i = -1;
	tid = pthread_self();
	while (++i < MAX_THREADS)
	{
		if (pthread_equal(stp->tids[i], tid))
			break ;
	}
	coord.y = -1;
	while (++coord.y < HEIGHT)
	{
		coord.x = (WIDTH / MAX_THREADS) * i;
		while (coord.x < (WIDTH / MAX_THREADS) * (i + 1))
		{
			bship(coord, stp, i);
			coord.x++;
		}
	}
	pthread_exit(0);
}
