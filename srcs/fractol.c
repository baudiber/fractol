/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 23:05:57 by baudiber          #+#    #+#             */
/*   Updated: 2018/09/28 18:53:49 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		quitfdf(void)
{
	exit(1);
	return (0);
}

int		repeat_k(int key, t_setup *stp)
{
	if (stp->f_tree)
		return (0);
	else if (key == ARROW_UP)
		stp->prev.y -= 10;
	else if (key == ARROW_DOWN)
		stp->prev.y += 10;
	else if (key == ARROW_LEFT)
		stp->prev.x -= 10;
	else if (key == ARROW_RIGHT)
		stp->prev.x += 10;
	draw(stp);
	return (0);
}

void	fractol(t_setup *stp)
{
	if (!stp->f_tree)
		draw(stp);
	else
		fractal_tree(stp);
	mlx_key_hook(stp->win, stp_key, stp);
	mlx_hook(stp->win, 17, 0L, quitfdf, NULL);
	mlx_hook(stp->win, 2, (1L << 0), repeat_k, stp);
	if (stp->av[0] == 'j')
		mlx_hook(stp->win, 6, (1L << 6), julia_mouse, stp);
	mlx_mouse_hook(stp->win, mouse, stp);
	mlx_loop(stp->mlx);
}
