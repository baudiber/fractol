#include "fractol.h"

void	mandel(double x, double y, t_setup *stp)
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
		stp->frac.z_i = stp->frac.z_r * stp->frac.z_i;
		stp->frac.z_i += stp->frac.z_i;
		stp->frac.z_i += stp->frac.c_i;
		stp->frac.z_r = rsqr - isqr + stp->frac.c_r;
		rsqr = SQR(stp->frac.z_r);
		isqr = SQR(stp->frac.z_i);
		i++;
	}
	if (i == stp->frac.iteration_max)
		mlx_pixel_put_to_image(stp, x, y, 0);
		//stp->img[(int)x + (int)y * WIDTH] = 0;
	else
		mlx_pixel_put_to_image(stp, x, y, ((i * 0xFF / stp->frac.iteration_max) << 16) + (i * 0xFF / stp->frac.iteration_max));
		//stp->img[(int)x + (int)y * WIDTH] = ((i * 0xFF / stp->frac.iteration_max) << 16) + (i * 0xFF / stp->frac.iteration_max);
}

void	*draw_mandelbrot(void *arg)
{
	t_setup *stp = (t_setup *)arg;
	double	x;
	double	y;
	int		i;
	pthread_t tid;

	i = 0;
	tid = pthread_self();	
	while (i < MAX_THREADS)
	{
		if (pthread_equal(stp->tids[i], tid))
		{
			printf("%d\n", i);
			break;
		}
		i++;
	}
	y = 0;
	while (y < HEIGHT)
	{
		x = (WIDTH / MAX_THREADS) * i;
		while (x < (WIDTH / MAX_THREADS) * (i + 1))
		{
			mandel(x, y, stp);
			x++;
		}
		y++;
	}
	pthread_exit(0);
}
