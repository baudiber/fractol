/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   res.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 17:24:19 by baudiber          #+#    #+#             */
/*   Updated: 2018/10/22 23:16:51 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_res(t_setup *stp)
{
	stp->res[0][0] = 640;
	stp->res[0][1] = 480;
	stp->res[1][0] = 1024;
	stp->res[1][1] = 768;
	stp->res[2][0] = 1440;
	stp->res[2][1] = 900;
	stp->res[3][0] = 1920;
	stp->res[3][1] = 1080;
	stp->res[4][0] = 2560;
	stp->res[4][1] = 1420;
	stp->w = 640;
}

/*
** closes window and image and reinitialize windows to a new resolution
*/

void	change_res(t_setup *stp)
{
	if (stp->resi != 4)
		stp->resi++;
	else
		stp->resi = 0;
	stp->w = stp->res[stp->resi][0];
	mlx_destroy_image(stp->mlx, stp->img_ptr);
	mlx_destroy_window(stp->mlx, stp->win);
	init_mlx(stp);
	fractol(stp);
}
