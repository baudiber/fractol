/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 22:35:28 by baudiber          #+#    #+#             */
/*   Updated: 2018/08/06 22:37:48 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mandel(t_xy xy, t_setup *stp, int tid)
{
	double	isqr;
	double	rsqr;
	int		i;

	stp->tmp[tid].z_r = 0;
	stp->tmp[tid].z_i = 0;
	stp->tmp[tid].c_r = xy.x / stp->tmp[tid].zoom + stp->tmp[tid].x1;
	stp->tmp[tid].c_i = xy.y / stp->tmp[tid].zoom + stp->tmp[tid].y1;
	rsqr = stp->tmp[tid].z_r * stp->tmp[tid].z_r;
	isqr = stp->tmp[tid].z_i * stp->tmp[tid].z_i;
	i = 0;
	while (rsqr + isqr < 4 && i < stp->tmp[tid].iteration_max)
	{
		stp->tmp[tid].z_i = stp->tmp[tid].z_r * stp->tmp[tid].z_i;
		stp->tmp[tid].z_i += stp->tmp[tid].z_i;
		stp->tmp[tid].z_i += stp->tmp[tid].c_i;
		stp->tmp[tid].z_r = rsqr - isqr + stp->tmp[tid].c_r;
		rsqr = SQR(stp->tmp[tid].z_r);
		isqr = SQR(stp->tmp[tid].z_i);
		i++;
	}
	set_pixel(i, stp, tid, &xy);
}

void	*draw_mandelbrot(void *arg)
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
	xy.y = -1;
	while (++xy.y < HEIGHT)
	{
		xy.x = (WIDTH / MAX_THREADS) * i;
		while (xy.x < (WIDTH / MAX_THREADS) * (i + 1))
		{
			mandel(xy, stp, i);
			xy.x++;
		}
	}
	pthread_exit(0);
}
