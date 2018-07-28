/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_pixel_put_to_image.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roddavid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 19:18:23 by roddavid          #+#    #+#             */
/*   Updated: 2018/06/15 00:50:21 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mlx_pixel_put_to_image(t_setup *stp, int x, int y, int color)
{
	int			i;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	i = x * (stp->bpx / 8) + y * stp->s_line;
	stp->img[i] = color % 256;
	color /= 256;
	stp->img[i + 1] = color % 256;
	color /= 256;
	stp->img[i + 2] = color % 256;
	color /= 256;
	stp->img[i + 3] = 0;
	color /= 256;
}
