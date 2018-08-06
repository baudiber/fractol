/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 19:55:11 by baudiber          #+#    #+#             */
/*   Updated: 2018/08/06 19:55:24 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	set_pixel(int i, t_setup *stp, int tid, t_xy *xy)
{
	if (i == stp->tmp[tid].iteration_max)
		stp->img[(int)xy->x + (int)xy->y * WIDTH] = 0;
	else if (i > stp->tmp[tid].iteration_max / 3)
		stp->img[(int)xy->x + (int)xy->y * WIDTH] = ((i * 0xFF \
			/ stp->tmp[tid].iteration_max) << 16) \
			+ ((i * 0xFF / stp->tmp[tid].iteration_max) << 8);
	else
		stp->img[(int)xy->x + (int)xy->y * WIDTH] = ((i * 0xFF \
			/ stp->tmp[tid].iteration_max + 30) << 16);
}
