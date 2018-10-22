/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baudiber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 22:53:30 by baudiber          #+#    #+#             */
/*   Updated: 2018/10/23 00:47:07 by baudiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define WIDTH 640
# define HEIGHT 480
# define MAX_THREADS 32
# define SCROLL_DOWN 5
# define SCROLL_UP 4
# define ECHAP 53
# define SPACE 49
# define KEY_I 34
# define KEY_X 7
# define KEY_K 40
# define KEY_W 13
# define KEY_S 1
# define KEY_J 38
# define KEY_H 4
# define KEY_C 8
# define KEY_R 15
# define ARROW_UP 126
# define ARROW_DOWN 125
# define ARROW_LEFT 123
# define ARROW_RIGHT 124

# include "../minilibx/minilibx_mac/mlx.h"
# include "../libft/libft.h"
# include <math.h>
# include <pthread.h>

typedef struct s_setup	t_setup;
typedef struct s_frac	t_frac;
typedef struct s_xy		t_xy;
typedef struct s_pt		t_pt;
typedef struct s_bres	t_bres;
typedef struct s_tree	t_tree;

struct			s_tree
{
	int		length;
	int		brnchs;
	int		scale;
	int		pos_y;
	double	rot;
	double	depth;
	float	rot_scale;
	int		offset_x;
	int		offset_y;
	double	dir_x;
	double	dir_y;
};

struct			s_xy
{
	double		x;
	double		y;
};

struct			s_frac
{
	double				x1;
	double				y1;
	unsigned long int	zoom;
	int					max_iter;
	double				c_r;
	double				c_i;
	double				z_r;
	double				tmp;
	double				z_i;
};

struct			s_pt
{
	float			x;
	float			y;
	unsigned int	color;
};

struct			s_bres
{
	int				cumul;
	int				i;
	int				x;
	int				y;
	int				dx;
	int				dy;
	int				xinc;
	int				yinc;
};

/*
** main struct
*/

struct			s_setup
{
	pthread_t		tids[MAX_THREADS];
	pthread_attr_t	attr;
	t_frac			tmp[MAX_THREADS];
	t_frac			frac;
	t_tree			tree;
	t_xy			prev;
	void			*(*ft_frac)();
	char			*av;
	char			*mlx;
	char			*win;
	char			*img_ptr;
	int				degrad;
	int				rainbow;
	int				hud;
	int				juliamouse;
	int				f_tree;
	int				treerand;
	int				crosshair;
	int				*img;
	int				bpx;
	int				s_line;
	int				ed;
	int				n;
	int				resi;
	int				res[5][2];
	int				w;
};

/*
** init functions
*/

void			init_mlx(t_setup *stp);
void			init_var(t_setup *stp);
void			init_res(t_setup *stp);
void			fractol(t_setup *stp);
void			change_res(t_setup *stp);

/*
** events (keyboard and mouse)
*/

int				frac_key(int key, t_setup *stp);
int				mouse(int button, int x, int y, t_setup *stp);
int				julia_mouse(int x, int y, t_setup *stp);
int				repeat_k(int key, t_setup *stp);

/*
** drawing functions
*/

void			draw(t_setup *stp);
void			*draw_julia(void *arg);
void			*draw_juliargh(void *arg);
void			*draw_juliaiaia(void *arg);
void			*draw_mandelbrot(void *arg);
void			*draw_bship(void *arg);
void			*draw_tricorn(void *arg);
void			*draw_multibrot3(void *arg);
void			*draw_multibrot(void *arg);
void			set_pixel(int i, t_setup *stp, int tid, t_xy *xy);
void			set_rainbow(int i, t_setup *stp, int tid, t_xy *xy);
void			ft_bresenham(t_pt p1, t_pt p2, t_bres *bres, int **img);
void			fractal_tree(t_setup *stp);

/*
** multithreading
*/

int				find_thread(t_setup *stp);

/*
** math func
*/

int				ft_abs(int val);
double			rand_fl(void);

#endif
