/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 23:05:57 by baudiber          #+#    #+#             */
/*   Updated: 2018/07/11 22:23:39 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		quitfdf(void)
{
	exit(1);
	return (0);
}

void	fractol(t_setup *stp)
{	
	init(stp);
	draw(stp);
	//garder ca c'est le non repeat key
	mlx_key_hook(stp->win, stp_key, stp);
//	mlx_hook(stp->win, 2, (1L << 0), stp_key, stp);
	mlx_hook(stp->win, 17, 0L, quitfdf, NULL);
	if (stp->av[0] == 'j')
		mlx_hook(stp->win, 6, (1L << 6), julia_mouse, stp);
	mlx_mouse_hook(stp->win, mouse_move, stp);
	mlx_loop(stp->mlx);
}
