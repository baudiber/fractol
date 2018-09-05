/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 19:55:11 by baudiber          #+#    #+#             */
/*   Updated: 2018/09/03 18:04:05 by baudiber         ###   ########.fr       */
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

void	set_rainbow(int i, t_setup *stp, int tid, t_xy *xy)
{
	int	degrad;

	degrad = stp->tmp[tid].iteration_max / 7;
	if (i < degrad)
 		stp->img[(int)xy->x + (int)xy->y * WIDTH] = ((i * 0xFF \
<<<<<<< HEAD
			/ degrad + 10) << 16);
=======
			/ degrad /2 + 30) << 16);
>>>>>>> 63663f6111c67ac490b0ea1bbbb20a412a6fbfca
	else if (i < degrad * 2)
		stp->img[(int)xy->x + (int)xy->y * WIDTH] = (0xFF << 16) + ((i * 0xFF / degrad * 2 + 30) << 8);
	else if (i < degrad * 3)
		stp->img[(int)xy->x + (int)xy->y * WIDTH] = (0xFF << 8) + ((i * 0xFF / degrad * 3 + 30) << 16);
	else if (i < degrad * 4)
		stp->img[(int)xy->x + (int)xy->y * WIDTH] = (0xFF << 8) + (i * 0xFF / degrad * 4 + 30);
	else if (i < degrad * 5)
		stp->img[(int)xy->x + (int)xy->y * WIDTH] = 0xFF + ((i * 0xFF / degrad * 5 + 30) << 8);
	else if (i < degrad * 6)
		stp->img[(int)xy->x + (int)xy->y * WIDTH] = 0xFF + ((i * 0xFF / degrad * 6 + 30) << 16);
	else if (i < degrad * 7)
		stp->img[(int)xy->x + (int)xy->y * WIDTH] = (0xFF << 16) + (i * 0xFF / degrad * 7 + 30);
	else
		stp->img[(int)xy->x + (int)xy->y * WIDTH] = 0;
}
