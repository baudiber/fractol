/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 19:53:36 by baudiber          #+#    #+#             */
/*   Updated: 2018/09/18 19:22:59 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double rand_fl(void)
{
	double test;

	test = (double)rand() / (double)RAND_MAX;
	return (0.5);
}

void	draw_bg(int **img)
{
	int		i;

	i = 0;
	while (i < WIDTH * HEIGHT)
		(*img)[i++] = 0xFFFFFF;
}

void	draw_tree(int offsetX, int offsetY, double dirX, double dirY, double length, double rot, double depth, t_setup *stp)
{
	t_pt p1;
	t_pt p2;
	t_bres	bres;

	p1.x = offsetX;
	p1.y = offsetY;
	p2.x = (int)(offsetX + dirX * length);
	p2.y = (int)(offsetY + dirY * length);
	p2.color = 0;
	ft_bresenham(p1, p2, &bres, &stp->img);	
	if (depth > 0)
	{
		draw_tree(offsetX + dirX * length, offsetY + dirY * length, dirX * cos(rot) + dirY * sin(rot), dirX * -sin(rot) + dirY * cos(rot), length * rand_fl() / stp->tree.scale + length * (stp->tree.scale - 1) / stp->tree.scale, rot * stp->tree.rot_scale, depth - 1, stp); 
		draw_tree(offsetX + dirX * length, offsetY + dirY * length, dirX * cos(-rot) + dirY * sin(-rot), dirX * -sin(-rot) + dirY * cos(-rot), length * rand_fl() / stp->tree.scale + length * (stp->tree.scale - 1) / stp->tree.scale, rot * stp->tree.rot_scale, depth - 1, stp); 
	}
}

void	fractal_tree(t_setup *stp)
{
	draw_bg(&stp->img);
	draw_tree(0, stp->tree.y, 0.0, -1.0, stp->tree.length, M_PI / 8, stp->tree.brnchs, stp);
	mlx_put_image_to_window(stp->img, stp->win, stp->img_ptr, 0, 0);
}
