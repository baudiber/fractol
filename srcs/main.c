/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 22:52:59 by baudiber          #+#    #+#             */
/*   Updated: 2018/07/12 00:55:33 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	which_frac(t_setup *stp)
{
	if (!ft_strcmp(stp->av, "mandelbrot"))
		stp->mandelbrot = 1;
	else if (!ft_strcmp(stp->av, "julia"))
		stp->julia = 1;
}

int		main(int ac, char **av)
{
	t_setup stp;

	if (ac > 2)
		ft_putendl("usage : ./fractol or ./fractol <mandelbrot> / <julia>");
	else if (ac == 2 && ((ft_strcmp(av[1], "julia")) && (ft_strcmp(av[1], "mandelbrot"))))
		ft_putendl("usage : ./fractol or ./fractol <mandelbrot> / <julia>");
	else
	{
		ft_bzero(&stp, sizeof(t_setup));
		if (ac == 2)
		{
			stp.av = av[1];
			which_frac(&stp);
		}
		else
			stp.splash = 1;
		init_all(&stp);
		fractol(&stp);
	}
	return (0);	
}
