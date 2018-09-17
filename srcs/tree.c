/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 19:53:36 by baudiber          #+#    #+#             */
/*   Updated: 2018/09/17 22:14:01 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
# define INITIAL_LENGTH 75
# define BRANCHES 10
# define SCALE 5
# define ROT_SCALE 0.90

double rand_fl(void)
{
	  return (double)rand() / (double)RAND_MAX;
}

void	draw_bg(int **img)
{
	int		i;

	i = 0;
	while (i < WIDTH * HEIGHT)
		(*img)[i++] = 0xFFFFFF;
}

void	draw_tree(double offsetX, double offsetY, double dirX, double dirY, double size, double rot, double depth, t_setup *stp)
{
	t_pt p1;
	t_pt p2;
	t_bres	bres;

	p1.x = (int)offsetX;
	p1.y = (int)offsetY;
	p2.x = (int)(offsetX + dirX * size);
	p2.y = (int)(offsetY + dirY * size);
	p2.color = 0;
	ft_bresenham(p1, p2, &bres, &stp->img);	
	if (depth > 0)
	{
		draw_tree(offsetX + dirX * size, offsetY + dirY * size, dirX * cos(rot) + dirY * sin(rot), dirX * -sin(rot) + dirY * cos(rot), size * rand_fl() / SCALE + size * (SCALE - 1) / SCALE, rot * ROT_SCALE, depth - 1, stp); 
		draw_tree(offsetX + dirX * size, offsetY + dirY * size, dirX * cos(-rot) + dirY * sin(-rot), dirX * -sin(-rot) + dirY * cos(-rot), size * rand_fl() / SCALE + size * (SCALE - 1) / SCALE, rot * ROT_SCALE, depth - 1, stp); 
	}
}

void	fractal_tree(t_setup *stp)
{
	draw_bg(&stp->img);
	draw_tree(0, 300, 0.0, -1.0, INITIAL_LENGTH, M_PI / 8, BRANCHES, stp);
	mlx_put_image_to_window(stp->img, stp->win, stp->img_ptr, 0, 0);
}
