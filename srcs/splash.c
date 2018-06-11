/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splash.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 23:15:26 by baudiber          #+#    #+#             */
/*   Updated: 2018/06/11 23:25:40 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	splash_art(t_setup *stp)
{
	int				i;
	unsigned int	j;

	i = 0;
	j = 0xFFFFFFFF;
	while (i < WIDTH)
	{
		stp->img[WIDTH * HEIGHT / 2 + i] = j;
		if (i < WIDTH / 2 && j > 0x00FFFFFF)
			j -= 0x01000000;
		if (i >= WIDTH - (WIDTH * 25 / 100) && j < 0xFFFFFFFF)
			j += 0x01000000;
		i++;
	}
}

void	display_splash(t_setup *stp)
{
	splash_art(stp);
	mlx_put_image_to_window(stp->img, stp->win, stp->img_ptr, 0, 0);
	mlx_string_put(stp->mlx, stp->win, WIDTH / 2 - 50, \
			HEIGHT / 2 - 20, 0xFFFFFF, "Fractol v0.1");
}
