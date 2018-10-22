/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 19:53:36 by baudiber          #+#    #+#             */
/*   Updated: 2018/10/22 23:00:23 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** redraws background in white
*/

void	draw_bg(int **img)
{
	int		i;

	i = 0;
	while (i < WIDTH * HEIGHT)
		(*img)[i++] = 0xFFFFFF;
}

t_tree	next_tree(t_tree *prevtree, int dir, t_setup *stp)
{
	t_tree	t1;
	double	rand;
	double	rot;

	rot = (dir) ? prevtree->rot : -prevtree->rot;
	t1.offset_x = prevtree->offset_x + prevtree->dir_x * prevtree->length;
	t1.offset_y = prevtree->offset_y + prevtree->dir_y * prevtree->length;
	t1.dir_x = prevtree->dir_x * cos(rot) + prevtree->dir_y \
		* sin(rot);
	t1.dir_y = prevtree->dir_x * -sin(rot) + prevtree->dir_y \
		* cos(rot);
	rand = (stp->treerand) ? rand_fl() : 0.5;
	t1.length = prevtree->length * rand / stp->tree.scale + prevtree->length \
		* (stp->tree.scale - 1) / stp->tree.scale;
	t1.rot = prevtree->rot * stp->tree.rot_scale;
	t1.depth = prevtree->depth - 1;
	return (t1);
}

/*
** *recursion alert*
** tree algorithm
**		tree algorithm
** 			tree algorithm
*/

void	draw_tree(t_tree *prevtree, t_setup *stp)
{
	t_pt	p1;
	t_pt	p2;
	t_tree	t1;
	t_tree	t2;
	t_bres	bres;

	p1.x = prevtree->offset_x;
	p1.y = prevtree->offset_y;
	p2.x = (int)(prevtree->offset_x + prevtree->dir_x * prevtree->length);
	p2.y = (int)(prevtree->offset_y + prevtree->dir_y * prevtree->length);
	p2.color = 0;
	ft_bresenham(p1, p2, &bres, &stp->img);
	if (prevtree->depth > 0)
	{
		t1 = next_tree(prevtree, 1, stp);
		t2 = next_tree(prevtree, 0, stp);
		draw_tree(&t1, stp);
		draw_tree(&t2, stp);
	}
}

/*
** display tree HUD
*/

void	display_info_tree(t_setup *stp)
{
	char	*tmp;

	mlx_string_put(stp->mlx, stp->win, 5, 5, 0, "Length: ");
	mlx_string_put(stp->mlx, stp->win, 80, 5, 0, \
		(tmp = ft_itoa(stp->tree.length)));
	free(tmp);
	mlx_string_put(stp->mlx, stp->win, 5, 30, 0, "Depth: ");
	mlx_string_put(stp->mlx, stp->win, 70, 30, 0, \
		(tmp = ft_itoa(stp->tree.brnchs)));
	free(tmp);
}

/*
** Tree fractal
*/

void	fractal_tree(t_setup *stp)
{
	t_tree	starttree;

	draw_bg(&stp->img);
	bzero(&starttree, sizeof(t_tree));
	starttree.offset_y = stp->tree.pos_y;
	starttree.dir_y = -1.0;
	starttree.length = stp->tree.length;
	starttree.rot = M_PI / 8;
	starttree.depth = stp->tree.brnchs;
	draw_tree(&starttree, stp);
	mlx_put_image_to_window(stp->img, stp->win, stp->img_ptr, 0, 0);
	if (stp->hud)
		display_info_tree(stp);
}
