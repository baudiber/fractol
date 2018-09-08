/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 23:00:31 by baudiber          #+#    #+#             */
/*   Updated: 2018/09/05 17:31:51 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init(t_setup *stp)
{
	stp->frac.iteration_max = 150;
	stp->rainbow = 0;
	stp->prev.x = 0;
	stp->prev.y = 0;
	if (stp->av[0] == 'b')
	{
		stp->frac.x1 = -2.5;
		stp->frac.y1 = -2;
		stp->frac.zoom = 150;
	}
	if (stp->av[0] == 't')
	{
		stp->frac.x1 = -2.2;
		stp->frac.y1 = -1.5;
		stp->frac.zoom = 150;
	}
	if (stp->av[0] == 'm')
	{
		stp->frac.x1 = -2.3;
		stp->frac.y1 = -1.2;
		stp->frac.zoom = 200;
	}
	if (stp->av[0] == 'j')
	{
		stp->frac.x1 = -1.7;
		stp->frac.y1 = -1.2;
		stp->frac.zoom = 200;
		stp->frac.c_r = 0.285;
		stp->frac.c_i = 0.01;
	}
}

void	init_all(t_setup *stp)
{
	stp->mlx = mlx_init();
	stp->win = mlx_new_window(stp->mlx, WIDTH, HEIGHT, stp->av ? stp->av : "fractol");
	stp->img_ptr = mlx_new_image(stp->mlx, WIDTH, HEIGHT);
	stp->img = (int *)mlx_get_data_addr(stp->img_ptr, &stp->bpx, &stp->s_line, &stp->ed);
}
