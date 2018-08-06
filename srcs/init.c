/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 23:00:31 by baudiber          #+#    #+#             */
/*   Updated: 2018/07/29 00:45:39 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	create_window(char *str, t_setup *stp)
{
	stp->win = mlx_new_window(stp->mlx, WIDTH, HEIGHT, str);
}

void	init(t_setup *stp)
{
	stp->frac.iteration_max = 150;
	if (stp->bship)
	{
		stp->frac.x1 = -2.5;
		stp->frac.y1 = -2;
		stp->frac.zoom = 250;
	}
	if (stp->tricorn)
	{
		stp->frac.x1 = -2.2;
		stp->frac.y1 = -1.5;
		stp->frac.zoom = 250;
	}
	if (stp->multibrot3 || stp->multibrot || stp->mandelbrot)
	{
		stp->frac.x1 = -2.5;
		stp->frac.y1 = -1;
		stp->frac.zoom = 268;
		if (stp->multibrot)
			stp->frac.iteration_max = 20;
	}
	if (stp->julia)
	{
		stp->frac.x1 = -1.7;
		stp->frac.y1 = -1.2;
		stp->frac.zoom = 300;
		stp->frac.c_r = 0.285;
		stp->frac.c_i = 0.01;
	}
}

void	init_all(t_setup *stp)
{
	stp->mlx = mlx_init();
	create_window("fractol", stp);
	stp->img_ptr = mlx_new_image(stp->mlx, WIDTH, HEIGHT);
	//stp->img = mlx_get_data_addr(stp->img_ptr, &stp->bpx, &stp->s_line, &stp->ed);
	stp->img = (int *)mlx_get_data_addr(stp->img_ptr, &stp->bpx, &stp->s_line, &stp->ed);
}
