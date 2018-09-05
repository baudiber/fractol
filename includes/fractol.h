/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 22:53:30 by baudiber          #+#    #+#             */
/*   Updated: 2018/09/05 17:30:57 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define WIDTH 800
# define HEIGHT 600
# define ABS(x) ((x > 0) ? x : -x)
# define SQR(x) (x * x)
# define MAX_THREADS 32
# define SCROLL_DOWN 4
# define SCROLL_UP 5
# define ECHAP 53
# define KEY_I 34
# define KEY_K 40
# define KEY_W 13
# define KEY_S 1
# define KEY_C 8
# define ARROW_UP 126
# define ARROW_DOWN 125
# define ARROW_LEFT 123
# define ARROW_RIGHT 124

# include "mlx.h"
# include <stdio.h>
# include "libft.h"
# include <math.h>
# include <pthread.h>

typedef struct s_setup t_setup;
typedef struct s_frac t_frac;
typedef struct s_xy t_xy;


struct			s_xy
{
	double		x;
	double		y;
};

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
	pthread_t		tids[MAX_THREADS];
	pthread_attr_t	attr;
	t_frac 		tmp[MAX_THREADS];
	t_frac 		frac;
	t_xy		prev;
	void		*(*ft_frac)();
	char		*av;
	char		*mlx;
	char		*win;	
	char		*img_ptr;
	int			rainbow;
	int			*img;
	int			bpx;
	int			s_line;
	int			ed;
	int			n;
};

void			init_all(t_setup *stp);
void			fractol(t_setup *stp);
void			display_splash(t_setup *stp);
int				stp_key(int key, t_setup *stp);
int				mouse_move(int button, int x, int y, t_setup *stp);
int				julia_mouse(int x, int y, t_setup *stp);
void			draw(t_setup *stp);
void			init(t_setup *stp);
void			*draw_julia(void *arg);
void			*draw_mandelbrot(void *arg);
void			*draw_bship(void *arg);
void			*draw_tricorn(void *arg);
void			*draw_multibrot3(void *arg);
void			*draw_multibrot(void *arg);
void			set_pixel(int i, t_setup *stp, int tid, t_xy *xy);
void			set_rainbow(int i, t_setup *stp, int tid, t_xy *xy);

#endif
