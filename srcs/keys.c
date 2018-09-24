/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 23:27:34 by baudiber          #+#    #+#             */
/*   Updated: 2018/09/18 19:16:48 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
//remove that
#include <stdio.h>

void	zoom_in(t_setup *stp, int x, int y)
{
	printf("x :%d\n", x - WIDTH / 2);
	printf("y :%d\n", y - HEIGHT / 2);
	stp->frac.zoom *= 1.3;
	stp->prev.x += x - WIDTH / 2;
	stp->prev.y += y - HEIGHT / 2;
	stp->prev.x *= 1.3;
	stp->prev.y *= 1.2;
}

void	zoom_out(t_setup *stp, int x, int y)
{
	stp->prev.x -= x / 5;
	stp->prev.y -= y / 4;
	stp->prev.x *= 0.8;
	stp->prev.y *= 0.8;
	stp->frac.zoom *= 0.8;
}

int		mouse(int button, int x, int y, t_setup *stp)
{
	if (y < 3 || stp->f_tree)
		return (0);
	if (button == 1 && stp->frac.zoom <= 2000000000)
		zoom_in(stp, x, y);
	if (button == 2 && stp->frac.zoom >= 20)
		zoom_out(stp, x, y);
	if (button == SCROLL_UP && stp->frac.zoom <= 2000000000)
		zoom_in(stp, x, y);
	if (button == SCROLL_DOWN && stp->frac.zoom >= 20)
		zoom_out(stp, x, y);
	draw(stp);
	return (0);
}

int		julia_mouse(int x, int y, t_setup *stp)
{
	if (!stp->juliamouse || y < 3 || x < 0 || x > WIDTH || y > HEIGHT)
		return (0);
	stp->frac.c_r = x * (3.0 / WIDTH) - 1.5;
	stp->frac.c_i = y * (3.0 / HEIGHT) - 1.5;
	draw(stp);
	return (0);
}

int		tree_keys(int key, t_setup *stp)
{
	if (!stp->f_tree)
		return (0);
	if (key == ECHAP)
		exit(0);
	else if (key == ARROW_DOWN)
		stp->tree.y += 10;
	else if (key == ARROW_UP)
		stp->tree.y -= 10;
	else if (key == ARROW_RIGHT)
		stp->tree.length += 10;
	else if (key == ARROW_LEFT)
		stp->tree.length -= 10;
	else if (key == KEY_I)
		stp->tree.brnchs += 2;
	else if (key == KEY_K)
		stp->tree.brnchs -= 2;
	fractal_tree(stp);
	return (0);
}

int		stp_key(int key, t_setup *stp)
{
	if (stp->f_tree)
		tree_keys(key, stp);
	else
	{
		if (key == ARROW_UP)
			stp->prev.y -= 10;
		else if (key == ARROW_DOWN)
			stp->prev.y += 10;
		else if (key == ARROW_LEFT)
			stp->prev.x -= 10;
		else if (key == ARROW_RIGHT)
			stp->prev.x += 10;
		else if (key == SPACE)
			stp->juliamouse = (stp->juliamouse) ? 0 : 1;	
		else if (key == ECHAP)
			exit(0);
		else if (key == KEY_I && stp->frac.max_iter <= 1000)
			stp->frac.max_iter += 20;
		else if (key == KEY_K && stp->frac.max_iter > 20)
			stp->frac.max_iter -= 20;
		else if (key == KEY_H)
			stp->hud = (stp->hud) ? 0 : 1;
		else if (key == KEY_C)
			stp->rainbow = (stp->rainbow) ? 0 : 1;
		else if (key == KEY_R)
		{
			init(stp);
			ft_putendl("reset!");
		}
		draw(stp);
	}
	return (0);
}
