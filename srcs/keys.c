/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 23:27:34 by baudiber          #+#    #+#             */
/*   Updated: 2018/07/05 00:24:41 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

int		mouse_move(int button, int x, int y, t_setup *stp)
{
	if (button == 1)
	{
		//stp->frac.x1 = x * (double)(4 / WIDTH);
		//stp->frac.y1 = y * (double)(4 / HEIGHT);
		//printf("%f, %f\n", stp->frac.x1, stp->frac.y1);
		stp->frac.z_r = stp->frac.z_r + stp->frac.zoom * x;
		stp->frac.z_i = stp->frac.z_i + stp->frac.zoom * y;
		stp->frac.zoom *= 2;
	}
	if (button == 2)
	{
		stp->frac.c_r = stp->frac.c_r + stp->frac.zoom * x;
		stp->frac.c_i = stp->frac.c_i + stp->frac.zoom * y;
		stp->frac.zoom /= 2;
	}
	//6 = scroll down
	if (button == 4)
	{
		stp->frac.zoom += 10;
	}
	if (button == 5)
	{
		stp->frac.zoom -= 10;
	}
	draw(stp);
	printf("%d\n", button);
	return (0);
}

int		julia_mouse(int x, int y, t_setup *stp)
{
	stp->frac.c_r = x * (3.0 / WIDTH) - 1;
	stp->frac.c_i = y * (2.0 / HEIGHT) - 1;
	//printf("%f, %f\n", stp->frac.c_r, stp->frac.c_i);
	draw(stp);
	return (0);
}

int		stp_key(int key, t_setup *stp)
{
	if (key == 53)
		exit(0);
	if (key == 49)
	{
		stp->mandelbrot = 1;
	}
	//w
	if (key == 13)
	{
		stp->frac.zoom *= 1.2;
	}
	//s
	if (key == 1)
	{
		stp->frac.zoom /= 1.2;
	}
	draw(stp);
	return (0);
}
