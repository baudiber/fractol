/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 01:09:26 by baudiber          #+#    #+#             */
/*   Updated: 2018/08/06 20:11:33 by baudiber         ###   ########.fr       */
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

//free ft_itoa
void	info(t_setup *stp)
{
	mlx_string_put(stp->mlx, stp-> win, 5, 5, 0xFFFFFF, "Zoom: ");
	if (stp->frac.zoom < 2000000000 && stp->frac.zoom > 20)
		mlx_string_put(stp->mlx, stp->win, 60, 5, 0xFFFFFF, \
			ft_itoa(stp->frac.zoom));
	else if (stp->frac.zoom <= 20)
		mlx_string_put(stp->mlx, stp->win, 60, 5, 0xFFFFFF, "MIN");
	else	
		mlx_string_put(stp->mlx, stp->win, 60, 5, 0xFFFFFF, "MAX");
	mlx_string_put(stp->mlx, stp-> win, 5, 30, 0xFFFFFF, "Iterations: ");
	if (stp->frac.max_iter < 1000 && stp->frac.max_iter > 20)
		mlx_string_put(stp->mlx, stp->win, 120, 30, 0xFFFFFF, \
		ft_itoa(stp->frac.max_iter));
	else if (stp->frac.max_iter <= 20)
		mlx_string_put(stp->mlx, stp->win, 120, 30, 0xFFFFFF, "MIN");
	else
		mlx_string_put(stp->mlx, stp->win, 120, 30, 0xFFFFFF, "MAX");
}

void	draw(t_setup *stp)
{
	int		i;

	reset_img(&stp->img);
	if (stp->rainbow)
		stp->degrad = stp->frac.max_iter / 7;
	i = 0;
	while (i < MAX_THREADS)
	{
		stp->tmp[i] = stp->frac;
		pthread_create(&stp->tids[i], NULL, stp->ft_frac, stp); 
		i++;
	}
	i = 0;
	while (i < MAX_THREADS)
		pthread_join(stp->tids[i++], NULL);	
	mlx_put_image_to_window(stp->img, stp->win, stp->img_ptr, 0, 0);
	if (stp->hud)
		info(stp);
}
