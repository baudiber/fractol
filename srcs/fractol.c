/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 23:05:57 by baudiber          #+#    #+#             */
/*   Updated: 2018/06/29 01:07:24 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init(t_setup *stp)
{
	stp->mandel.x1 = -2.1;
	stp->mandel.y1 = -1.2;
	stp->mandel.zoom = 268;
	stp->mandel.iteration_max = 100;
}

void	fractol(t_setup *stp)
{	
	init(stp);
	display_splash(stp);
	mlx_key_hook(stp->win, stp_key, stp);
	mlx_loop(stp->mlx);
}
