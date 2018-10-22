/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 23:27:34 by baudiber          #+#    #+#             */
/*   Updated: 2018/10/23 00:28:40 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** function for keystrokes with keyrepeat ON
** (doesn't work for the fractal tree)
*/

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

/*
** keyboard events (no repeat) for TREE fractal
*/

int		tree_keys(int key, t_setup *stp)
{
	if (!stp->f_tree)
		return (0);
	if (key == ECHAP)
		exit(0);
	else if (key == ARROW_DOWN)
		stp->tree.pos_y += 10;
	else if (key == ARROW_UP)
		stp->tree.pos_y -= 10;
	else if (key == ARROW_RIGHT && stp->tree.length < 200)
		stp->tree.length += 10;
	else if (key == ARROW_LEFT && stp->tree.length > -200)
		stp->tree.length -= 10;
	else if (key == KEY_I && stp->tree.brnchs < 20)
		stp->tree.brnchs += 2;
	else if (key == KEY_K && stp->tree.brnchs > 0)
		stp->tree.brnchs -= 2;
	else if (key == KEY_R)
		stp->treerand = (stp->treerand) ? 0 : 1;
	else if (key == KEY_H)
		stp->hud = (stp->hud) ? 0 : 1;
	fractal_tree(stp);
	return (0);
}

/*
** keyboard events (no repeat)
*/

int		frac_key(int key, t_setup *stp)
{
	if (stp->f_tree)
		tree_keys(key, stp);
	else
	{
		if (key == SPACE)
			stp->juliamouse = (stp->juliamouse) ? 0 : 1;
		else if (key == KEY_J)
			change_res(stp);
		else if (key == KEY_X)
			stp->crosshair = (stp->crosshair) ? 0 : 1;
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
			init_var(stp);
		draw(stp);
	}
	return (0);
}
