#include "fractol.h"

void	tricorn(double x, double y, t_setup *stp)
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
	while (rsqr + isqr < 4 && i < stp->frac.iteration_max)
	{
		stp->frac.tmp = rsqr - isqr + stp->frac.c_r;
		stp->frac.z_i = -2 * stp->frac.z_r * stp->frac.z_i + stp->frac.c_i;
		stp->frac.z_r = stp->frac.tmp;
		rsqr = SQR(stp->frac.z_r);
		isqr = SQR(stp->frac.z_i);
		i++;
	}
	pthread_mutex_lock(&stp->mutex);
	if (i == stp->frac.iteration_max)
		//stp->img[(int)x + (int)y * WIDTH] = 0;
		mlx_pixel_put_to_image(stp, x, y, 0);
	else
		//mlx_pixel_put_to_image(stp, x, y, ((i * 0xFF / stp->frac.iteration_max) << 16) + (i * 0xFF / stp->frac.iteration_max));
		mlx_pixel_put_to_image(stp, x, y, (i * 0xFF / stp->frac.iteration_max) << 8);
	pthread_mutex_unlock(&stp->mutex);
		//stp->img[(int)x + (int)y * WIDTH] = ((i * 0xFF / stp->frac.iteration_max) << 16) + (i * 0xFF / stp->frac.iteration_max);
}

void	*draw_tricorn(void *arg)
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
			tricorn(x, y, stp);
			x++;
		}
		y++;
	}
	pthread_exit(0);
}
