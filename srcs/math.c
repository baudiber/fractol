/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 22:52:44 by baudiber          #+#    #+#             */
/*   Updated: 2018/10/22 22:57:10 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** returns a random very small float
*/

double	rand_fl(void)
{
	return ((double)rand() / (double)RAND_MAX);
}

/*
** a recreation of the abs BSD function
*/

int		ft_abs(int val)
{
	return ((val < 0) ? -val : val);
}
