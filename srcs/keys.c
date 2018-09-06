/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 23:27:34 by baudiber          #+#    #+#             */
/*   Updated: 2018/07/11 23:20:41 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

int		mouse_move(int button, int x, int y, t_setup *stp)
{
	if (y < 3)
		return (0);
	if (button == 1)
	{
		stp->prev.x += x / 5;
		stp->prev.y += y / 5;
		stp->prev.x *= 1.2;
		stp->prev.y *= 1.2;
		stp->frac.zoom *= 1.2;
	}
	if (button == 2)
	{
		stp->prev.x -= x / 5;
		stp->prev.y -= y / 5;
		stp->prev.x *= 0.8;
		stp->prev.y *= 0.8;
		stp->frac.zoom *= 0.8;
	}
	if (button == SCROLL_UP)
	{
		stp->prev.x += x / 5;
		stp->prev.y += y / 5;
		stp->prev.x *= 1.2;
		stp->prev.y *= 1.2;
		stp->frac.zoom *= 1.2;
	}
	if (button == SCROLL_DOWN)
	{
		stp->prev.x -= x / 5;
		stp->prev.y -= y / 5;
		stp->prev.x *= 0.8;
		stp->prev.y *= 0.8;
		stp->frac.zoom *= 0.8;
	}
	draw(stp);
//	printf("%d\n", button);
	return (0);
}

int		julia_mouse(int x, int y, t_setup *stp)
{
	if (y < 3)
		return (0);
	stp->frac.c_r = x * (3.0 / WIDTH) - 1.5;
	stp->frac.c_i = y * (2.0 / HEIGHT) - 1.5;
	draw(stp);
	return (0);
}

int		stp_key(int key, t_setup *stp)
{
	if (key == ECHAP)
		exit(0);
	if (key == KEY_I)
		stp->frac.iteration_max += 2;
	if (key == KEY_K)
		stp->frac.iteration_max -= 2;
	if (key == ARROW_UP)
		stp->frac.y1 -= 0.1;
	if (key == ARROW_DOWN)
		stp->frac.y1 += 0.1;
	if (key == ARROW_LEFT)
		stp->frac.x1 -= 0.1;
	if (key == ARROW_RIGHT)
		stp->frac.x1 += 0.1;
	if (key == KEY_C)
		stp->rainbow = (stp->rainbow) ? 0 : 1;
	if (key == KEY_W)
	{
		stp->prev.x *= 1.2;
		stp->prev.y *= 1.2;
		stp->frac.zoom *= 1.2;
	}
	if (key == KEY_S)
	{
		stp->prev.x *= 0.8;
		stp->prev.y *= 0.8;
		stp->frac.zoom *= 0.8;
	}
	draw(stp);
	return (0);
}
