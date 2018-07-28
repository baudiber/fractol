#include "fractol.h"

void	draw_julia(t_setup *stp)
{
	double	x;
	double	y;
	double	rsqr;
	double	isqr;
	int		i;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			stp->frac.z_r = x / stp->frac.zoom + stp->frac.x1;
			stp->frac.z_i = y / stp->frac.zoom + stp->frac.y1;
			rsqr = stp->frac.z_r * stp->frac.z_r;
			isqr = stp->frac.z_i * stp->frac.z_i;
			i = 0;
			while (rsqr + isqr < 4 && i < stp->frac.iteration_max)
			{
				stp->frac.tmp = stp->frac.z_r;
				stp->frac.z_r = rsqr - isqr + stp->frac.c_r;
				stp->frac.z_i = 2 * stp->frac.z_i * stp->frac.tmp + stp->frac.c_i;
				rsqr = SQR(stp->frac.z_r);
				isqr = SQR(stp->frac.z_i);
				i++;
			}
//			stp->img[(int)x + (int)y * WIDTH] = stp->color[i];
			if (i == stp->frac.iteration_max)
				mlx_pixel_put_to_image(stp, x, y, 0);
			//	stp->img[(int)x + (int)y * WIDTH] = 0;
			else
			//	stp->img[(int)x + (int)y * WIDTH] = stp->color[i];
				mlx_pixel_put_to_image(stp, x, y, ((i * 0xFF / stp->frac.iteration_max) << 16) + (i * 0xFF / stp->frac.iteration_max));
			//	stp->img[(int)x + (int)y * WIDTH] = ((i * 0xFF / stp->frac.iteration_max) << 16) + (i * 0xFF / stp->frac.iteration_max);
			x++;
		}
		y++;
	}
}

