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

void	bship(t_xy *xy, t_setup *stp, int tid)
{
	double	rsqr;
	double	isqr;
	int		i;

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
	if (stp->rainbow)
		set_rainbow(i, stp, tid, xy);
	else
		set_pixel(i, stp, tid, xy);
}

void	*draw_bship(void *arg)
{
	t_setup		*stp;
	t_xy		xy;
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
	xy.y = stp->prev.y;
	while (++xy.y < HEIGHT + stp->prev.y)
	{
		xy.x = (WIDTH / MAX_THREADS) * i + stp->prev.x;
		while (xy.x < (WIDTH / MAX_THREADS) * (i + 1) + stp->prev.x)
		{
			stp->tmp[i].z_r = 0;
			stp->tmp[i].z_i = 0;
			stp->tmp[i].c_r = xy.x / stp->tmp[i].zoom + stp->tmp[i].x1;
			stp->tmp[i].c_i = xy.y / stp->tmp[i].zoom + stp->tmp[i].y1;
			bship(&xy, stp, i);
			xy.x++;
		}
	}
	pthread_exit(0);
}
