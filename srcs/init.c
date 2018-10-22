/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 23:00:31 by baudiber          #+#    #+#             */
/*   Updated: 2018/10/23 00:51:25 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	frac_init(t_setup *stp)
{
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
		stp->frac.x1 = -2.3;
	if (stp->av[0] == 'j')
	{
		stp->frac.x1 = -1.6;
		stp->frac.c_r = 0.285;
		stp->frac.c_i = 0.01;
	}
}

/*
** initialise variables for fractals
*/

void	init_var(t_setup *stp)
{
	stp->frac.max_iter = 155;
	bzero(&stp->prev, sizeof(t_xy));
	stp->juliamouse = 1;
	stp->hud = 1;
	stp->crosshair = 0;
	stp->frac.zoom = 200;
	stp->frac.y1 = -1.2;
	frac_init(stp);
	if (stp->av[3] == 't')
	{
		stp->frac.x1 = -1.7;
		stp->frac.max_iter = 45;
	}
	if (stp->av[2] == 'e')
	{
		stp->f_tree = 1;
		stp->tree.length = 50;
		stp->tree.brnchs = 10;
		stp->tree.scale = 5;
		stp->tree.rot_scale = 0.90;
		stp->tree.pos_y = 180;
	}
}

void	init_mlx(t_setup *stp)
{
	stp->mlx = mlx_init();
	stp->win = mlx_new_window(stp->mlx, stp->res[stp->resi][0], \
		stp->res[stp->resi][1], "fractol");
	stp->img_ptr = mlx_new_image(stp->mlx, stp->res[stp->resi][0], \
		stp->res[stp->resi][1]);
	stp->img = (int *)mlx_get_data_addr(stp->img_ptr, \
		&stp->bpx, &stp->s_line, &stp->ed);
}
