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
	double x1 = -2.1;
	double y1 = -1.2;
	int zoom = 268; // pour une distance de 1 sur le plan, on a 100 pixel sur l'image
	int iteration_max = 100;
	double x;
	double y;
	double	c_r;
	double	c_i;
	double	z_r;
	double	tmp;
	double	z_i;
	int		i;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			c_r = x / zoom + x1;
			c_i = y / zoom + y1;
			z_r = 0;
			z_i = 0;
			i = 0;
			while ((z_r * z_r) + (z_i * z_i) < 4 && i < iteration_max)
			{
				tmp = z_r;
				z_r = (z_r * z_r) - (z_i * z_i) + c_r;
				z_i = 2 * z_i * tmp + c_i;
				i++;
			}
			if (i == iteration_max)
			//	mlx_pixel_put_to_image(stp->img_ptr, x , y, 0);
				stp->img[(int)x + (int)y * WIDTH] = 0;
			else
			//	mlx_pixel_put_to_image(stp->img_ptr, x , y, (i * 0x0000FF / iteration_max));
				stp->img[(int)x + (int)y * WIDTH] = ((i * 0xFF / iteration_max) << 16) + (i * 0xFF / iteration_max);
			x++;
		}
		y++;
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
