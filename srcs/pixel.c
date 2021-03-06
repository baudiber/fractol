/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 19:55:11 by baudiber          #+#    #+#             */
/*   Updated: 2018/10/23 00:05:02 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** this function sets the color to a nice red / orange warm range
*/

void	set_pixel(int i, t_setup *stp, int tid, t_xy *xy)
{
	if (i == stp->tmp[tid].max_iter)
		stp->img[(int)(xy->x - stp->prev.x) + (int)(xy->y - stp->prev.y) \
			* stp->w] = 0;
	else if (i > stp->tmp[tid].max_iter / 3)
		stp->img[(int)(xy->x - stp->prev.x) + (int)(xy->y - stp->prev.y) \
			* stp->w] = ((i * 0xFF / stp->tmp[tid].max_iter) << 16) \
			+ ((i * 0xFF / stp->tmp[tid].max_iter) << 8);
	else
		stp->img[(int)(xy->x - stp->prev.x) + (int)(xy->y - stp->prev.y) \
			* stp->w] = ((i * 0xFF / stp->tmp[tid].max_iter + 30) << 16);
}

/*
** degrad is the number max of iteration divided by 7
** i is the iteration value
** this functions changes the color of the pixel according the value of i
** in a rainbow manner
*/

void	set_rainbow(int i, t_setup *stp, int tid, t_xy *xy)
{
	if (i < stp->degrad)
		stp->img[(int)(xy->x - stp->prev.x) + (int)(xy->y - stp->prev.y) \
	* stp->w] = ((i * 0xFF / stp->tmp[tid].max_iter + 30) << 8);
	else if (i < stp->degrad * 2)
		stp->img[(int)(xy->x - stp->prev.x) + (int)(xy->y - stp->prev.y) \
	* stp->w] = (0xFF << 16) + ((i * 0xFF / stp->degrad * 2 + 30) << 8);
	else if (i < stp->degrad * 3)
		stp->img[(int)(xy->x - stp->prev.x) + (int)(xy->y - stp->prev.y) \
	* stp->w] = (0xFF << 8) + ((i * 0xFF / stp->degrad * 3 + 30) << 16);
	else if (i < stp->degrad * 4)
		stp->img[(int)(xy->x - stp->prev.x) + (int)(xy->y - stp->prev.y) \
	* stp->w] = (0xFF << 8) + (i * 0xFF / stp->degrad * 4 + 30);
	else if (i < stp->degrad * 5)
		stp->img[(int)(xy->x - stp->prev.x) + (int)(xy->y - stp->prev.y) \
	* stp->w] = 0xFF + ((i * 0xFF / stp->degrad * 5 + 30) << 8);
	else if (i < stp->degrad * 6)
		stp->img[(int)(xy->x - stp->prev.x) + (int)(xy->y - stp->prev.y) \
	* stp->w] = 0xFF + ((i * 0xFF / stp->degrad * 6 + 30) << 16);
	else if (i < stp->degrad * 7)
		stp->img[(int)(xy->x - stp->prev.x) + (int)(xy->y - stp->prev.y) \
	* stp->w] = (0xFF << 16) + (i * 0xFF / stp->degrad * 7 + 30);
	else
		stp->img[(int)(xy->x - stp->prev.x) + (int)(xy->y - stp->prev.y) \
	* stp->w] = 0;
}
