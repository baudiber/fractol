/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 22:43:00 by baudiber          #+#    #+#             */
/*   Updated: 2018/10/23 00:15:11 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zoom_in(t_setup *stp, int x, int y)
{
	stp->prev.x += x - stp->res[stp->resi][0] / 2;
	stp->prev.y += y - stp->res[stp->resi][1] / 2;
	stp->frac.zoom *= 1.2;
	stp->prev.x *= 1.2;
	stp->prev.y *= 1.2;
	stp->prev.x += stp->res[stp->resi][0] / 10 - 2;
	stp->prev.y += stp->res[stp->resi][1] / 10 - 2;
}

void	zoom_out(t_setup *stp, int x, int y)
{
	stp->prev.x += x - stp->res[stp->resi][0] / 2;
	stp->prev.y += y - stp->res[stp->resi][1] / 2;
	stp->prev.x *= 0.8;
	stp->prev.y *= 0.8;
	stp->frac.zoom *= 0.8;
	stp->prev.x -= stp->res[stp->resi][0] / 10 - 2;
	stp->prev.y -= stp->res[stp->resi][1] / 10 - 2;
}

/*
** mouse events handling
*/

int		mouse(int button, int x, int y, t_setup *stp)
{
	if (y < 3 || stp->f_tree)
		return (0);
	if (button == 1 && stp->frac.zoom <= 2000000000)
		zoom_in(stp, x, y);
	if (button == 2 && stp->frac.zoom >= 20)
		zoom_out(stp, x, y);
	if (button == SCROLL_UP && stp->frac.zoom <= 2000000000)
		zoom_in(stp, x, y);
	if (button == SCROLL_DOWN && stp->frac.zoom >= 20)
		zoom_out(stp, x, y);
	draw(stp);
	return (0);
}

/*
** transform the Julia fractal according to x y mouse coordinates
*/

int		julia_mouse(int x, int y, t_setup *stp)
{
	if (!stp->juliamouse || y < 3 || x < 0 || x > stp->res[stp->resi][0] \
			|| y > stp->res[stp->resi][1])
		return (0);
	stp->frac.c_r = x * (3.0 / stp->res[stp->resi][0]) - 1.5;
	stp->frac.c_i = y * (3.0 / stp->res[stp->resi][1]) - 1.5;
	draw(stp);
	return (0);
}
