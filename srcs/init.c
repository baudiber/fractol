/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 23:00:31 by baudiber          #+#    #+#             */
/*   Updated: 2018/07/11 23:25:20 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	create_window(char *str, t_setup *stp)
{
	stp->win = mlx_new_window(stp->mlx, WIDTH, HEIGHT, str);
}

void	init(t_setup *stp)
{
	if (stp->mandelbrot)
	{
		stp->frac.x1 = -2.5;
		stp->frac.y1 = -1.4;
		stp->frac.zoom = 268;
		stp->frac.iteration_max = 100;
	}
	if (stp->julia)
	{
		stp->frac.x1 = -1.7;
		stp->frac.y1 = -1.2;
		stp->frac.zoom = 300;
		stp->frac.iteration_max = 100;
		stp->frac.c_r = 0.285;
		stp->frac.c_i = 0.01;
	}
}

void	init_all(t_setup *stp)
{
	stp->mlx = mlx_init();
	create_window("fractol", stp);
	stp->img_ptr = mlx_new_image(stp->mlx, WIDTH, HEIGHT);
	stp->img = (int *)mlx_get_data_addr(stp->img_ptr, &stp->bpx, &stp->s_line, &stp->ed);
}
