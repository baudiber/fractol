#include "fractol.h"

void	bship(double x, double y, t_setup *stp)
{
	double	rsqr;
	double	isqr;
	int		i;

	stp->frac.z_r = 0;
	stp->frac.z_i = 0;
	stp->frac.c_r = x / stp->frac.zoom + stp->frac.x1;
	stp->frac.c_i = y / stp->frac.zoom + stp->frac.y1;
	rsqr = stp->frac.z_r * stp->frac.z_r;
	isqr = stp->frac.z_i * stp->frac.z_i;
	i = 0;
	while (rsqr + isqr < (1 << 16) && i < stp->frac.iteration_max)
	{
		stp->frac.tmp = rsqr - isqr + stp->frac.c_r;
		stp->frac.z_i = ABS(2 * stp->frac.z_r * stp->frac.z_i) + stp->frac.c_i;
		stp->frac.z_r = ABS(stp->frac.tmp);
		rsqr = SQR(stp->frac.z_r);
		isqr = SQR(stp->frac.z_i);
		i++;
	}
	if (i == stp->frac.iteration_max)
	//	stp->img[(int)x + (int)y * WIDTH] = 0;
		mlx_pixel_put_to_image(stp, x, y, 0);
	else
	//	stp->img[(int)x + (int)y * WIDTH] = stp->color[i];
		mlx_pixel_put_to_image(stp, x, y, ((i * 0xFF / stp->frac.iteration_max) << 9) + (i * 0xFF / stp->frac.iteration_max));
		//stp->img[(int)x + (int)y * WIDTH] = ((i * 0xFF / stp->frac.iteration_max) << 16) + (i * 0xFF / stp->frac.iteration_max);
}

void	draw_bship(t_setup *stp)
{
	double	x;
	double	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			bship(x, y, stp);
			x++;
		}
		y++;
	}
}
