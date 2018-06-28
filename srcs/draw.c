/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 01:09:26 by baudiber          #+#    #+#             */
/*   Updated: 2018/06/29 01:09:28 by baudiber         ###   ########.fr       */
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
	int		i;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			stp->mandel.c_r = x / stp->mandel.zoom + stp->mandel.x1;
			stp->mandel.c_i = y / stp->mandel.zoom + stp->mandel.y1;
			stp->mandel.z_r = 0;
			stp->mandel.z_i = 0;
			i = 0;
			while ((stp->mandel.z_r * stp->mandel.z_r) + (stp->mandel.z_i * stp->mandel.z_i) < 4 && i < stp->mandel.iteration_max)
			{
				stp->mandel.tmp = stp->mandel.z_r;
				stp->mandel.z_r = (stp->mandel.z_r * stp->mandel.z_r) - (stp->mandel.z_i * stp->mandel.z_i) + stp->mandel.c_r;
				stp->mandel.z_i = 2 * stp->mandel.z_i * stp->mandel.tmp + stp->mandel.c_i;
				i++;
			}
			if (i == stp->mandel.iteration_max)
				stp->img[(int)x + (int)y * WIDTH] = 0;
			else
				stp->img[(int)x + (int)y * WIDTH] = ((i * 0xFF / stp->mandel.iteration_max) << 16) + (i * 0xFF / stp->mandel.iteration_max);
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
	//else if (stp->julia)
	mlx_put_image_to_window(stp->img, stp->win, stp->img_ptr, 0, 0);
}
