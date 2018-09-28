/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 01:09:26 by baudiber          #+#    #+#             */
/*   Updated: 2018/09/28 23:30:58 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	info(t_setup *stp)
{
	char	*tmp;

	mlx_string_put(stp->mlx, stp->win, 5, 30, 0xFFFFFF, "Zoom: ");
	if (stp->frac.zoom < 2000000000 && stp->frac.zoom > 20)
	{
		mlx_string_put(stp->mlx, stp->win, 60, 30, 0xFFFFFF, \
			(tmp = ft_itoa(stp->frac.zoom)));
		free(tmp);
	}
	else if (stp->frac.zoom <= 20)
		mlx_string_put(stp->mlx, stp->win, 60, 30, 0xFFFFFF, "MIN");
	else
		mlx_string_put(stp->mlx, stp->win, 60, 30, 0xFFFFFF, "MAX");
	mlx_string_put(stp->mlx, stp->win, 5, 55, 0xFFFFFF, "Iterations: ");
	if (stp->frac.max_iter < 1000 && stp->frac.max_iter > 20)
	{
		mlx_string_put(stp->mlx, stp->win, 120, 55, 0xFFFFFF, \
		(tmp = ft_itoa(stp->frac.max_iter)));
		free(tmp);
	}
	else if (stp->frac.max_iter <= 20)
		mlx_string_put(stp->mlx, stp->win, 120, 55, 0xFFFFFF, "MIN");
	else
		mlx_string_put(stp->mlx, stp->win, 120, 55, 0xFFFFFF, "MAX");
}

void	display_res(t_setup *stp)
{
	char	*tmp;

	mlx_string_put(stp->mlx, stp->win, 5, 5, 0xFFFFFF, "Resolution: ");
	mlx_string_put(stp->mlx, stp->win, 120, 5, 0xFFFFFF, \
		(tmp = ft_itoa(stp->res[stp->resi][0])));
	free(tmp);
	mlx_string_put(stp->mlx, stp->win, 160, 5, 0xFFFFFF, "x");
	mlx_string_put(stp->mlx, stp->win, 170, 5, 0xFFFFFF, \
		(tmp = ft_itoa(stp->res[stp->resi][1])));
	free(tmp);
}

void	draw(t_setup *stp)
{
	int		i;

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
	{
		display_res(stp);
		info(stp);
	}
}
