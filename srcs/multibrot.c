#include "fractol.h"

double	squaren(double src, int n)
{
	double	ret;

	ret = src;
	while (n--)
	{
		ret = src * ret;
	}
	return (ret);	
}

void	multibrot(double x, double y, t_setup *stp)
{
	double	isqr;
	double	rsqr;
	int		i;
	int		n;

	n = stp->n;
	stp->frac.z_r = 0;
	stp->frac.z_i = 0;
	stp->frac.c_r = x / stp->frac.zoom + stp->frac.x1;
	stp->frac.c_i = y / stp->frac.zoom + stp->frac.y1;
	rsqr = stp->frac.z_r * stp->frac.z_r;
	isqr = stp->frac.z_i * stp->frac.z_i;
	i = 0;
	while (rsqr + isqr < 8 && i < stp->frac.iteration_max)
	{
		stp->frac.tmp = squaren((rsqr + isqr), (n / 2)) * cos(n * atan2(stp->frac.z_i, stp->frac.z_r)) + stp->frac.c_r;
		stp->frac.z_i = squaren((rsqr + isqr), (n / 2)) * sin(n * atan2(stp->frac.z_i, stp->frac.z_r)) + stp->frac.c_i;
		stp->frac.z_r = stp->frac.tmp;
		rsqr = stp->frac.z_r * stp->frac.z_r;
		isqr = stp->frac.z_i * stp->frac.z_i;
		i++;
	}
	if (i == stp->frac.iteration_max)
		mlx_pixel_put_to_image(stp, x, y, 0xFFFFFF);
	else if (i < stp->frac.iteration_max - 10)
		mlx_pixel_put_to_image(stp, x, y, i * 0 / stp->frac.iteration_max);
		//mlx_pixel_put_to_image(stp, x, y, ((i * 0xFF / stp->frac.iteration_max) << 16) + (i * 0xFF / stp->frac.iteration_max));
	else
		mlx_pixel_put_to_image(stp, x, y, ((i * 0xFF / stp->frac.iteration_max) << 16 ) + ((i * 0xFF / stp->frac.iteration_max) << 8) + (i * 0xFF / stp->frac.iteration_max));
}

	//mandelbrot
	//	stp->frac.tmp = rsqr - isqr + stp->frac.c_r;
	//	stp->frac.z_i = 2 * stp->frac.z_r * stp->frac.z_i + stp->frac.c_i;
	//	stp->frac.z_r = stp->frac.tmp;

void	draw_multibrot(t_setup *stp)
{
	double	x;
	double	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			multibrot(x, y, stp);
			x++;
		}
		y++;
	}
}
