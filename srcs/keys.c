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
	if (button == 4)
	{
		stp->frac.x1 = x * (3.0 / WIDTH) - 3;
		stp->frac.y1 = y * (2.0 / HEIGHT) - 2; 
		stp->frac.zoom += 10;
	}
	if (button == 5)
	{
		stp->frac.x1 = x * (3.0 / WIDTH) - 3;
		stp->frac.y1 = y * (2.0 / HEIGHT) - 2; 
		stp->frac.zoom -= 10;
	}
	draw(stp);
//	printf("%d\n", button);
	return (0);
}

int		julia_mouse(int x, int y, t_setup *stp)
{
	if (y < 3)
		return (0);
	if (!stp->julia)
		return (0);
	//stp->frac.c_r = x * (3.0 / WIDTH) - 1;
	//stp->frac.c_i = y * (2.0 / HEIGHT) - 1;
	stp->frac.c_r = x * (3.0 / WIDTH) - 1.5;
	stp->frac.c_i = y * (2.0 / HEIGHT) - 1.5;
	draw(stp);
	return (0);
}

int		stp_key(int key, t_setup *stp)
{
	printf("%d\n", key);
	if (key == 53)
		exit(0);
	if (key == 49)
		stp->mandelbrot = 1;
	if (key == 34)
		stp->frac.iteration_max += 2;
	if (key == 40)
		stp->frac.iteration_max -= 2;
	if (key == 69)
		stp->frac.iteration_max += 1;
	if (key == 126)
		stp->frac.y1 -= 0.1;
	if (key == 125)
		stp->frac.y1 += 0.1;
	if (key == 123)
		stp->frac.x1 -= 0.1;
	if (key == 124)
		stp->frac.x1 += 0.1;
	if (key == 78)
		stp->frac.iteration_max -= 1;
	//w
	if (key == 13)
	{
		stp->frac.x1 /= 1.2;
		stp->frac.y1 /= 1.2;
		stp->frac.zoom *= 1.2;
	}
	//s
	if (key == 1)
	{
		stp->frac.x1 *= 1.2;
		stp->frac.y1 *= 1.2;
		stp->frac.zoom /= 1.2;
	}
	draw(stp);
	return (0);
}
