/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multibrot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 15:22:08 by baudiber          #+#    #+#             */
/*   Updated: 2018/09/12 15:24:47 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	squaren(double src, int n)
{
	double	ret;

	ret = src;
	while (n--)
	{
		ret = src * ret;
	}
	return (ret);
}

void	multibrot(t_xy *xy, t_setup *stp, int tid)
{
	double	isqr;
	double	rsqr;
	int		i;
	int		n;

	n = stp->n;
	rsqr = 0;
	isqr = 0;
	i = 0;
	while (rsqr + isqr < 8 && i++ < stp->tmp[tid].max_iter)
	{
		stp->tmp[tid].tmp = squaren((rsqr + isqr), (n / 2)) \
			* cos(n * atan2(stp->tmp[tid].z_i, stp->tmp[tid].z_r)) \
			+ stp->tmp[tid].c_r;
		stp->tmp[tid].z_i = squaren((rsqr + isqr), (n / 2)) \
			* sin(n * atan2(stp->tmp[tid].z_i, stp->tmp[tid].z_r)) \
			+ stp->tmp[tid].c_i;
		stp->tmp[tid].z_r = stp->tmp[tid].tmp;
		rsqr = stp->tmp[tid].z_r * stp->tmp[tid].z_r;
		isqr = stp->tmp[tid].z_i * stp->tmp[tid].z_i;
	}
	if (stp->rainbow)
		set_rainbow(i, stp, tid, xy);
	else
		set_pixel(i, stp, tid, xy);
}

void	*draw_multibrot(void *arg)
{
	t_setup *stp;
	t_xy	xy;
	int		i;

	stp = (t_setup *)arg;
	i = find_thread(stp);
	xy.y = stp->prev.y;
	while (++xy.y < HEIGHT + stp->prev.y)
	{
		xy.x = (WIDTH / MAX_THREADS) * i + stp->prev.x;
		while (xy.x < ((WIDTH / MAX_THREADS) * (i + 1)) + stp->prev.x)
		{
			stp->tmp[i].z_r = 0;
			stp->tmp[i].z_i = 0;
			stp->tmp[i].c_r = xy.x / stp->tmp[i].zoom + stp->tmp[i].x1;
			stp->tmp[i].c_i = xy.y / stp->tmp[i].zoom + stp->tmp[i].y1;
			multibrot(&xy, stp, i);
			xy.x++;
		}
	}
	pthread_exit(0);
}
