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
		stp->frac.x1 = x / stp->frac.zoom - 2.3;
		stp->frac.y1 = y / stp->frac.zoom - 1.2; 
		printf("%f, %f\n", stp->frac.x1, stp->frac.y1);
		printf("%d, %d\n", x, y);
		//stp->frac.zoom *= 1.2;
	}
	if (button == 2)
	{
		stp->frac.x1 = x * (0.2 / WIDTH) - 2.3;
		stp->frac.y1 = y * (0.12 / HEIGHT) - 1.2; 
		//stp->frac.zoom /= 1.2;
	}
	//6 = scroll down
	if (button == SCROLL_DOWN)
	{
		stp->frac.x1 = x;
		stp->frac.y1 = y;
		stp->frac.x1 /= 1.2;
		stp->frac.y1 /= 1.2;
		stp->frac.zoom *= 1.2;
	}
	if (button == SCROLL_UP)
	{
		stp->frac.x1 *= 1.2;
		stp->frac.y1 *= 1.2;
		stp->frac.zoom /= 1.2;
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
	printf("%d\n", key);
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
		stp->frac.x1 /= 1.2;
		stp->frac.y1 /= 1.2;
		stp->frac.zoom *= 1.2;
	}
	if (key == KEY_S)
	{
		stp->frac.x1 *= 1.2;
		stp->frac.y1 *= 1.2;
		stp->frac.zoom /= 1.2;
	}
	draw(stp);
	return (0);
}
