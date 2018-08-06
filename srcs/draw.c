/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 01:09:26 by baudiber          #+#    #+#             */
/*   Updated: 2018/07/29 00:45:42 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	reset_img(int **img)
{
	int		i;

	i = 0;
	while (i < WIDTH * HEIGHT)
		(*img)[i++] = 0;
}

void	draw(t_setup *stp)
{
	int		i;

	reset_img(&stp->img);
	i = 0;
	while (i < MAX_THREADS)
	{
		stp->tmp[i] = stp->frac;
		if (stp->mandelbrot)
			pthread_create(&stp->tids[i], NULL, draw_mandelbrot, stp); 
		else if (stp->julia)
			pthread_create(&stp->tids[i], NULL, draw_julia, stp); 
		else if (stp->tricorn)
			pthread_create(&stp->tids[i], NULL, draw_tricorn, stp); 
		else if (stp->bship)
			pthread_create(&stp->tids[i], NULL, draw_bship, stp); 
		else if (stp->multibrot3)
			pthread_create(&stp->tids[i], NULL, draw_multibrot3, stp); 
		else if (stp->multibrot)
			pthread_create(&stp->tids[i], NULL, draw_multibrot, stp); 
		i++;
	}
	i = 0;
	while (i < MAX_THREADS)
		pthread_join(stp->tids[i++], NULL);	

	mlx_put_image_to_window(stp->img, stp->win, stp->img_ptr, 0, 0);
}
