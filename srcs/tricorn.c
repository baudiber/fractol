/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tricorn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 15:22:44 by baudiber          #+#    #+#             */
/*   Updated: 2018/09/15 14:11:27 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	tricorn(t_xy *xy, t_setup *stp, int tid)
{
	double	rsqr;
	double	isqr;
	int		i;

	i = 0;
	rsqr = 0;
	isqr = 0;
	while (rsqr + isqr < 4 && i < stp->tmp[tid].max_iter)
	{
		stp->tmp[tid].tmp = rsqr - isqr + stp->tmp[tid].c_r;
		stp->tmp[tid].z_i = -2 * stp->tmp[tid].z_r * stp->tmp[tid].z_i \
			+ stp->tmp[tid].c_i;
		stp->tmp[tid].z_r = stp->tmp[tid].tmp;
		rsqr = ft_square_d(stp->tmp[tid].z_r);
		isqr = ft_square_d(stp->tmp[tid].z_i);
		i++;
	}
	if (stp->rainbow)
		set_rainbow(i, stp, tid, xy);
	else
		set_pixel(i, stp, tid, xy);
}

void	*draw_tricorn(void *arg)
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
			tricorn(&xy, stp, i);
			xy.x++;
		}
	}
	pthread_exit(0);
}
