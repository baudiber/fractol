/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 01:09:26 by baudiber          #+#    #+#             */
/*   Updated: 2018/07/11 22:18:50 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	reset_img(int **img)
{
	int		i;

	i = 0;
	while (i < WIDTH * HEIGHT)
		(*img)[i++] = 0;
}

void	draw_mandelbrot(t_setup *stp)
{
	double	x;
	double	y;
	double	rsqr;
	double	isqr;
	int		i;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			stp->frac.z_r = 0;
			stp->frac.z_i = 0;
			stp->frac.c_r = x / stp->frac.zoom + stp->frac.x1;
			stp->frac.c_i = y / stp->frac.zoom + stp->frac.y1;
			rsqr = stp->frac.z_r * stp->frac.z_r;
			isqr = stp->frac.z_i * stp->frac.z_i;
			i = 0;
			while (rsqr + isqr < 4 && i < stp->frac.iteration_max)
			{
				stp->frac.tmp = stp->frac.z_r;
				stp->frac.z_r = rsqr - isqr + stp->frac.c_r;
				stp->frac.z_i = 2 * stp->frac.z_i * stp->frac.tmp + stp->frac.c_i;
				rsqr = SQR(stp->frac.z_r);
				isqr = SQR(stp->frac.z_i);
				i++;
			}
			if (i == stp->frac.iteration_max)
				stp->img[(int)x + (int)y * WIDTH] = 0;
			else
				stp->img[(int)x + (int)y * WIDTH] = ((i * 0xFF / stp->frac.iteration_max) << 16) + (i * 0xFF / stp->frac.iteration_max);
			x++;
		}
		y++;
	}
}

void	draw_julia(t_setup *stp)
{
	double	x;
	double	y;
	double	rsqr;
	double	isqr;
	int		i;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			stp->frac.z_r = x / stp->frac.zoom + stp->frac.x1;
			stp->frac.z_i = y / stp->frac.zoom + stp->frac.y1;
			rsqr = stp->frac.z_r * stp->frac.z_r;
			isqr = stp->frac.z_i * stp->frac.z_i;
			i = 0;
			while (rsqr + isqr < 4 && i < stp->frac.iteration_max)
			{
				stp->frac.tmp = stp->frac.z_r;
				stp->frac.z_r = rsqr - isqr + stp->frac.c_r;
				stp->frac.z_i = 2 * stp->frac.z_i * stp->frac.tmp + stp->frac.c_i;
				rsqr = SQR(stp->frac.z_r);
				isqr = SQR(stp->frac.z_i);
				i++;
			}
			if (i == stp->frac.iteration_max)
				stp->img[(int)x + (int)y * WIDTH] = 0;
			else
				stp->img[(int)x + (int)y * WIDTH] = ((i * 0xFF / stp->frac.iteration_max) << 16) + (i * 0xFF / stp->frac.iteration_max);
			x++;
		}
		y++;
	}
}

void	draw(t_setup *stp)
{
	reset_img(&stp->img);
	if (stp->mandelbrot)
		draw_mandelbrot(stp);
	else if (stp->julia)
		draw_julia(stp);
	//pthread_create(&tid, &attr, 
	mlx_put_image_to_window(stp->img, stp->win, stp->img_ptr, 0, 0);
}
