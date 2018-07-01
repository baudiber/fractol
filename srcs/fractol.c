/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 23:05:57 by baudiber          #+#    #+#             */
/*   Updated: 2018/07/01 02:08:40 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		quitfdf(void)
{
	exit(1);
	return (0);
}

void	init(t_setup *stp)
{
//	if (stp->mandelbrot)
//	{
//		stp->frac.x1 = -2.1;
//		stp->frac.y1 = -1.2;
//		stp->frac.zoom = 268;
//		stp->frac.iteration_max = 100;
//	}
	stp->frac.x1 = -1.5;
	stp->frac.y1 = 1.5;
	stp->frac.zoom = 100;
	stp->frac.iteration_max = 150;
}

void	fractol(t_setup *stp)
{	
	pthread_attr_init(&stp->attr);
	init(stp);
	//display_splash(stp);
	draw(stp);
	//mlx_key_hook(stp->win, stp_key, stp);
	mlx_hook(stp->win, 2, (1L << 0), stp_key, stp);
	mlx_hook(stp->win, 17, 0L, quitfdf, NULL);
	mlx_mouse_hook(stp->win, mouse_move, stp);
	mlx_loop(stp->mlx);
}
