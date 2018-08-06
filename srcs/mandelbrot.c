#include "fractol.h"

void	mandel(double x, double y, t_setup *stp, int tid)
{
	double	isqr;
	double	rsqr;
	int		i;

	stp->tmp[tid].z_r = 0;
	stp->tmp[tid].z_i = 0;
	stp->tmp[tid].c_r = x / stp->tmp[tid].zoom + stp->tmp[tid].x1;
	stp->tmp[tid].c_i = y / stp->tmp[tid].zoom + stp->tmp[tid].y1;
	rsqr = stp->tmp[tid].z_r * stp->tmp[tid].z_r;
	isqr = stp->tmp[tid].z_i * stp->tmp[tid].z_i;
	i = 0;
	while (rsqr + isqr < 4 && i < stp->tmp[tid].iteration_max)
	{
		stp->tmp[tid].z_i = stp->tmp[tid].z_r * stp->tmp[tid].z_i;
		stp->tmp[tid].z_i += stp->tmp[tid].z_i;
		stp->tmp[tid].z_i += stp->tmp[tid].c_i;
		stp->tmp[tid].z_r = rsqr - isqr + stp->tmp[tid].c_r;
		rsqr = SQR(stp->tmp[tid].z_r);
		isqr = SQR(stp->tmp[tid].z_i);
		i++;
	}
	if (i == stp->tmp[tid].iteration_max)
		stp->img[(int)x + (int)y * WIDTH] = 0;
	else if (i > stp->tmp[tid].iteration_max / 3)
		stp->img[(int)x + (int)y * WIDTH] = ((i * 0xFF / stp->tmp[tid].iteration_max) << 16) + ((i * 0xFF / stp->tmp[tid].iteration_max) << 8);
	else
		stp->img[(int)x + (int)y * WIDTH] = ((i * 0xFF / stp->tmp[tid].iteration_max + 30) << 16);
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
			break;
		i++;
	}
	y = 0;
	while (y < HEIGHT)
	{
		x = (WIDTH / MAX_THREADS) * i;
		while (x < (WIDTH / MAX_THREADS) * (i + 1))
		{
			mandel(x, y, stp, i);
			x++;
		}
		y++;
	}
	pthread_exit(0);
}
