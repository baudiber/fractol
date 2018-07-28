#include "fractol.h"

void	multibrot3(double x, double y, t_setup *stp)
{
	double	isqr;
	double	rsqr;
	int		i;

	stp->frac.z_r = 0;
	stp->frac.z_i = 0;
	stp->frac.c_r = x / stp->frac.zoom + stp->frac.x1;
	stp->frac.c_i = y / stp->frac.zoom + stp->frac.y1;
	rsqr = stp->frac.z_r * stp->frac.z_r;
	isqr = stp->frac.z_i * stp->frac.z_i;
	i = 0;
	while (rsqr + isqr < 4 && i < stp->frac.iteration_max)
	{
		stp->frac.tmp = (rsqr * stp->frac.z_r) - 3 * stp->frac.z_r * isqr + stp->frac.c_r;
		stp->frac.z_i = 3 * rsqr * stp->frac.z_i - (isqr * stp->frac.z_i) + stp->frac.c_i;
		stp->frac.z_r = stp->frac.tmp;
		rsqr = stp->frac.z_r * stp->frac.z_r;
		isqr = stp->frac.z_i * stp->frac.z_i;
		i++;
	}
	if (i == stp->frac.iteration_max)
		mlx_pixel_put_to_image(stp, x, y, 0);
	else
		mlx_pixel_put_to_image(stp, x, y, ((i * 0xFF / stp->frac.iteration_max) << 16) + (i * 0xFF / stp->frac.iteration_max));
}

	//mandelbrot
	//	stp->frac.tmp = rsqr - isqr + stp->frac.c_r;
	//	stp->frac.z_i = 2 * stp->frac.z_r * stp->frac.z_i + stp->frac.c_i;
	//	stp->frac.z_r = stp->frac.tmp;

void	draw_multibrot3(t_setup *stp)
{
	double	x;
	double	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			multibrot3(x, y, stp);
			x++;
		}
		y++;
	}
}
