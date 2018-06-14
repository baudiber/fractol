/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 22:53:30 by baudiber          #+#    #+#             */
/*   Updated: 2018/06/15 00:46:57 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FRACTOL_H_
# define _FRACTOL_H_
# define WIDTH 1024
# define HEIGHT 724
# define ABS(x) ((x > 0) ? x : -x)

# include "mlx.h"
# include "libft.h"
# include <math.h>

typedef struct s_setup t_setup;

struct s_setup
{
	char	*av;
	char	*mlx;
	char	*win;	
	char	*img_ptr;
	int		*img;
	int		bpx;
	int		s_line;
	int		ed;
	int		mandelbrot;
};

void	init_all(t_setup *stp);
void	fractol(t_setup *stp);
void	display_splash(t_setup *stp);
int		stp_key(int key, t_setup *stp);
void	draw(t_setup *stp);
void	mlx_pixel_put_to_image(void *img, int x, int y, int color);

#endif
