/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 23:00:31 by baudiber          #+#    #+#             */
/*   Updated: 2018/06/11 23:23:11 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	create_window(char *str, t_setup *stp)
{
	stp->win = mlx_new_window(stp->mlx, WIDTH, HEIGHT, str);
}

void	init_all(t_setup *stp)
{
	stp->mlx = mlx_init();
	create_window(stp->av, stp);
	stp->img_ptr = mlx_new_image(stp->mlx, WIDTH, HEIGHT);
	stp->img = (int *)mlx_get_data_addr(stp->img_ptr, &stp->bpx, &stp->s_line, &stp->ed);
}
