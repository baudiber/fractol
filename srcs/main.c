/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 22:52:59 by baudiber          #+#    #+#             */
/*   Updated: 2018/08/06 20:05:41 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	which_frac(t_setup *stp)
{
	if (!ft_strcmp(stp->av, "mandelbrot"))
		stp->ft_frac = draw_mandelbrot;
	else if (!ft_strcmp(stp->av, "julia"))
		stp->ft_frac = draw_julia;
	else if (!ft_strcmp(stp->av, "tricorn"))
		stp->ft_frac = draw_tricorn;
	else if (!ft_strcmp(stp->av, "burningship"))
		stp->ft_frac = draw_bship;
	else if (!ft_strcmp(stp->av, "multibrot3"))
		stp->ft_frac = draw_multibrot3;
	else if (!ft_strcmp(stp->av, "multibrot"))
		stp->ft_frac = draw_multibrot;
}

void	print_help(void)
{
	ft_putendl("~~~~~~~~~ HELP ~~~~~~~~~~");
	ft_putendl("W/S keys: zoom");
	ft_putendl("Scroll wheel: zoom");
	ft_putendl("Arrow keys: pan");
	ft_putendl("I/K keys: add iterations");
	ft_putendl("~~~~~~~~~~~~~~~~~~~~~~~~~");
}

void	ft_errors(int type)
{
	if (type == 1)
		ft_putendl("usage : ./fractol <mandelbrot> / <julia> / <burningship> / <tricorn> / <multibrot3> / <multibrot> <1-100>");
	else if (type == 2)
		ft_putendl("multibrot number should be between 1 and 100");
	exit(0);
}

int		main(int ac, char **av)
{
	t_setup stp;
	int		i;

	if (ac > 3)
		ft_errors(1);
	else if (ac == 2 && ((ft_strcmp(av[1], "julia")) && (ft_strcmp(av[1], "mandelbrot")) && (ft_strcmp(av[1], "burningship")) && (ft_strcmp(av[1], "tricorn")) && (ft_strcmp(av[1], "multibrot3"))))
		ft_errors(1);
	else if (ac == 3 && (ft_strcmp(av[1], "multibrot")))
	{
		i = 0;
		while (av[2][i])
		{
			if (!ft_isdigit(av[2][i]))
				ft_errors(1);
			i++;
		}
	}
	if (ac == 3)
	{
		stp.n = ft_atoi(av[2]);
		if (stp.n > 100 || stp.n <= 0)
			ft_errors(2);
	}
	print_help();
	ft_bzero(&stp, sizeof(t_setup));
	stp.av = av[1];
	which_frac(&stp);
	init_all(&stp);
	fractol(&stp);
	return (0);	
}
