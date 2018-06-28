/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 22:53:30 by baudiber          #+#    #+#             */
/*   Updated: 2018/06/29 01:10:38 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define WIDTH 1024
# define HEIGHT 724
# define ABS(x) ((x > 0) ? x : -x)

# include "mlx.h"
# include "libft.h"
# include <math.h>

typedef struct s_setup t_setup;
typedef struct s_mandel t_mandel;

struct			s_mandel
{
	double		x1;
	double		y1;
	int			zoom;
	int 		iteration_max;
	double		c_r;
	double		c_i;
	double		z_r;
	double		tmp;
	double		z_i;
};

struct			s_setup
{
	t_mandel 	mandel;
	char		*av;
	char		*mlx;
	char		*win;	
	char		*img_ptr;
	int			*img;
	int			bpx;
	int			s_line;
	int			ed;
	int			mandelbrot;
};

void			init_all(t_setup *stp);
void			fractol(t_setup *stp);
void			display_splash(t_setup *stp);
int				stp_key(int key, t_setup *stp);
void			draw(t_setup *stp);

#endif
