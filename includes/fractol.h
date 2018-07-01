/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 22:53:30 by baudiber          #+#    #+#             */
/*   Updated: 2018/07/01 02:06:01 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define WIDTH 1024
# define HEIGHT 724
# define ABS(x) ((x > 0) ? x : -x)
# define SQR(x) (x * x)
# define H 10

# include "mlx.h"
# include "libft.h"
# include <math.h>
# include <pthread.h>

typedef struct s_setup t_setup;
typedef struct s_frac t_frac;

struct			s_frac
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
	pthread_t		tid;
	pthread_attr_t	attr;
	t_frac 		frac;
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
int				mouse_move(int button, int x, int y, t_setup *stp);
void			draw(t_setup *stp);

#endif
