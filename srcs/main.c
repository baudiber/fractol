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
	else if (!ft_strcmp(stp->av, "tricorn"))
		stp->tricorn = 1;
	else if (!ft_strcmp(stp->av, "burningship"))
		stp->bship = 1;
	else if (!ft_strcmp(stp->av, "multibrot3"))
		stp->multibrot3 = 1;
	else if (!ft_strcmp(stp->av, "multibrot"))
		stp->multibrot = 1;
}

int		main(int ac, char **av)
{
	t_setup stp;
	int		i;

	if (ac > 3)
	{
		ft_putendl("Too many arguments");
		return (0);
	}
	else if (ac == 2 && ((ft_strcmp(av[1], "julia")) && (ft_strcmp(av[1], "mandelbrot")) && (ft_strcmp(av[1], "burningship")) && (ft_strcmp(av[1], "tricorn")) && (ft_strcmp(av[1], "multibrot3"))))
	{
		ft_putendl("usage : ./fractol or ./fractol <mandelbrot> / <julia>");
		return (0);
	}
	else if (ac == 3 && (ft_strcmp(av[1], "multibrot")))
	{
		i = 0;
		while (av[2][i])
		{
			if (!ft_isdigit(av[2][i]))
			{
				ft_putendl("usage : ./fractol or ./fractol <mandelbrot> / <julia>");
				return (0);
			}
			i++;
		}
	}
	ft_bzero(&stp, sizeof(t_setup));
	if (ac > 1)
	{
		stp.av = av[1];
		which_frac(&stp);
		if (ac == 3)
			stp.n = ft_atoi(av[2]);
	}
	else
	{
		printf("ac = %d\n", ac);
		stp.splash = 1;
	}
	init_all(&stp);
	fractol(&stp);
	return (0);	
}
