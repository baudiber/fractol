/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 23:27:34 by baudiber          #+#    #+#             */
/*   Updated: 2018/06/29 01:06:07 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
		stp->mandel.zoom += 10;
		stp->mandel.iteration_max += 10;
	}
	//s
	if (key == 1)
	{
		stp->mandel.zoom -= 10;
		stp->mandel.iteration_max -= 10;
	}
	draw(stp);
	return (0);
}
