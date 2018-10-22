/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 22:31:47 by baudiber          #+#    #+#             */
/*   Updated: 2018/10/23 00:49:45 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	juliaiaia(t_xy *xy, t_setup *stp, int tid)
{
	double	rsqr;
	double	isqr;
	int		i;

	rsqr = stp->tmp[tid].z_r * stp->tmp[tid].z_r;
	isqr = stp->tmp[tid].z_i * stp->tmp[tid].z_i;
	i = 0;
	while (rsqr + isqr < 4 && i < stp->tmp[tid].max_iter)
	{
		stp->tmp[tid].tmp = stp->tmp[tid].z_r;
		stp->tmp[tid].z_r = rsqr - isqr + stp->tmp[tid].c_r;
		stp->tmp[tid].z_i = 1 * stp->tmp[tid].z_i * stp->tmp[tid].tmp \
			+ stp->tmp[tid].c_i;
		rsqr = stp->tmp[tid].z_r * stp->tmp[tid].z_r;
		isqr = stp->tmp[tid].z_i * stp->tmp[tid].z_i;
		i++;
	}
	if (stp->rainbow)
		set_rainbow(i, stp, tid, xy);
	else
		set_pixel(i, stp, tid, xy);
}

/*
** a cool version of julia
*/

void	*draw_juliaiaia(void *arg)
{
	t_setup		*stp;
	t_xy		xy;
	int			i;

	stp = (t_setup *)arg;
	i = find_thread(stp);
	xy.y = stp->prev.y;
	while (++xy.y < stp->res[stp->resi][1] + stp->prev.y)
	{
		xy.x = (stp->res[stp->resi][0] / MAX_THREADS) * i + stp->prev.x;
		while (xy.x < (stp->res[stp->resi][0] / MAX_THREADS) \
			* (i + 1) + stp->prev.x)
		{
			stp->tmp[i].z_r = xy.x / stp->tmp[i].zoom + stp->tmp[i].x1;
			stp->tmp[i].z_i = xy.y / stp->tmp[i].zoom + stp->tmp[i].y1;
			juliaiaia(&xy, stp, i);
			xy.x++;
		}
	}
	pthread_exit(0);
}
