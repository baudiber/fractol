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

void	multibrot(double x, double y, t_setup *stp, int tid)
{
	double	isqr;
	double	rsqr;
	int		i;
	int		n;

	n = stp->n;
	stp->tmp[tid].z_r = 0;
	stp->tmp[tid].z_i = 0;
	stp->tmp[tid].c_r = x / stp->tmp[tid].zoom + stp->tmp[tid].x1;
	stp->tmp[tid].c_i = y / stp->tmp[tid].zoom + stp->tmp[tid].y1;
	rsqr = stp->tmp[tid].z_r * stp->tmp[tid].z_r;
	isqr = stp->tmp[tid].z_i * stp->tmp[tid].z_i;
	i = 0;
	while (rsqr + isqr < 8 && i < 40)
	{
		stp->tmp[tid].tmp = squaren((rsqr + isqr), (n / 2)) * cos(n * atan2(stp->tmp[tid].z_i, stp->tmp[tid].z_r)) + stp->tmp[tid].c_r;
		stp->tmp[tid].z_i = squaren((rsqr + isqr), (n / 2)) * sin(n * atan2(stp->tmp[tid].z_i, stp->tmp[tid].z_r)) + stp->tmp[tid].c_i;
		stp->tmp[tid].z_r = stp->tmp[tid].tmp;
		rsqr = stp->tmp[tid].z_r * stp->tmp[tid].z_r;
		isqr = stp->tmp[tid].z_i * stp->tmp[tid].z_i;
		i++;
	}
	if (i == stp->tmp[tid].iteration_max)
		stp->img[(int)x + (int)y * WIDTH] = 0;
	else if (i > stp->tmp[tid].iteration_max / 3)
		stp->img[(int)x + (int)y * WIDTH] = ((i * 0xFF / stp->tmp[tid].iteration_max) << 16) + ((i * 0xFF / stp->tmp[tid].iteration_max) << 8);
	else
		stp->img[(int)x + (int)y * WIDTH] = ((i * 0xFF / stp->tmp[tid].iteration_max + 30) << 16);
}

void	*draw_multibrot(void *arg)
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
			multibrot(x, y, stp, i);
			x++;
		}
		y++;
	}
	pthread_exit(0);
}
