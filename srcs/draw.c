#include "fractol.h"

void	reset_img(int **img)
{
	int		i;

	i = 0;
	while (i < WIDTH * HEIGHT)
		(*img)[i++] = 0;
}

void	draw_mandelbrot(t_setup *stp)
{
	float x1 = -2.1;
	float x2 = 0.6;
	float y1 = -1.2;
	float y2 = 1.2;
	int zoom = 100; // pour une distance de 1 sur le plan, on a 100 pixel sur l'image
	int iteration_max = 50;
	int x = 0;
	int y = 0;
	float image_x = (x2 - x1) * zoom;
	float image_y = (y2 - y1) * zoom;
	float	c_r;
	float	c_i;
	float	z_r;
	float	tmp;
	float	z_i;
	int		i;

	while (x < image_x)
	{
		while (y < image_y)
		{
			c_r = x / zoom + x1;
			c_i = y / zoom + y1;
			z_r = 0;
			z_i = 0;
			i = 0;
			while (z_r * z_r + z_i * z_i < 4 && i < iteration_max)
			{
				tmp = z_r;
				z_r = z_r * z_r - z_i * z_i + c_r;
				z_i = 2 * z_i * tmp + c_i;
				i++;
			}
			if (i == iteration_max)
				stp->img[x + y * WIDTH] = 0;
			else
				stp->img[x + y * WIDTH] = i * 255 / iteration_max;
			y++;
		}
		x++;
	}
}

void	draw(t_setup *stp)
{
	reset_img(&stp->img);	
	if (stp->mandelbrot)
		draw_mandelbrot(stp);
	//else if (stp->julia)
	mlx_put_image_to_window(stp->img, stp->win, stp->img_ptr, 0, 0);
}
