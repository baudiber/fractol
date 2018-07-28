/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 01:09:26 by baudiber          #+#    #+#             */
/*   Updated: 2018/07/11 22:18:50 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
/*
void	reset_img(int **img)
{
	int		i;

	i = 0;
	while (i < WIDTH * HEIGHT)
		(*img)[i++] = 0;
}
*/
void	reset_img(char **img)
{
	int		i;

	i = 0;
	while (i < WIDTH * HEIGHT * 4)
		(*img)[i++] = 0;
}


void	draw(t_setup *stp)
{
	int		i;

	reset_img(&stp->img);
	if (stp->mandelbrot)
	{
		pthread_attr_init(&stp->attr);
		i = 0;
		while (i < MAX_THREADS)
		{
			pthread_create(&stp->tids[i], &stp->attr, draw_mandelbrot, stp); 
			i++;
		}
		i = 0;
		while (i < MAX_THREADS)
			pthread_join(stp->tids[i++], NULL);	
	}
	else if (stp->julia)
		draw_julia(stp);
	else if (stp->tricorn)
	{
		pthread_attr_init(&stp->attr);
		i = 0;
		while (i < MAX_THREADS)
		{
			pthread_create(&stp->tids[i], &stp->attr, draw_tricorn, stp); 
			i++;
		}
		i = 0;
		while (i < MAX_THREADS)
			pthread_join(stp->tids[i++], NULL);	
	}
	else if (stp->bship)
		draw_bship(stp);
	else if (stp->multibrot3)
		draw_multibrot3(stp);
	else if (stp->multibrot)
		draw_multibrot(stp);
	mlx_put_image_to_window(stp->img, stp->win, stp->img_ptr, 0, 0);
}
