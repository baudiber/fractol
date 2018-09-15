/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_squaren_d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 14:07:07 by baudiber          #+#    #+#             */
/*   Updated: 2018/09/15 14:07:09 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_squaren_d(double src, int n)
{
	double	ret;

	ret = src;
	while (n--)
	{
		ret = src * ret;
	}
	return (ret);
}
