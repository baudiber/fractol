/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 22:52:59 by baudiber          #+#    #+#             */
/*   Updated: 2018/06/11 23:22:54 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		main(int ac, char **av)
{
	t_setup stp;

	if (ac != 1)
		ft_putendl("usage : ./fractol");
	else
	{
		ft_bzero(&stp, sizeof(t_setup));
		stp.av = av[0];
		init_all(&stp);
		fractol(&stp);
	}
	return (0);	
}
