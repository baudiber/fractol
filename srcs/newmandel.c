void	draw_mandelbrot(t_setup *stp)
{
	double	x;
	double	y;
	double	zrsqr;
	double	zisqr;
	int		i;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			stp->frac.c_r = x / stp->frac.zoom + stp->frac.x1;
			stp->frac.c_i = y / stp->frac.zoom + stp->frac.y1;
			stp->frac.z_r = 0;
			stp->frac.z_i = 0;
			zrsqr = stp->frac.z_r * stp->frac.z_r;
			zisqr = stp->frac.z_i * stp->frac.z_i;
			i = 0;
			while ((zrsqr + zisqr) <= 4.0 && i < stp->frac.iteration_max)
			{
				stp->frac.z_i = sqrt(stp->frac.z_r + stp->frac.z_i) - zrsqr - zisqr; 
				stp->frac.z_i += stp->frac.c_i;
				stp->frac.z_r = zrsqr - zisqr + stp->frac.c_r;
				zrsqr = sqrt(stp->frac.z_r);
				zisqr = sqrt(stp->frac.z_i);
				i++;
			}
			if (i == stp->frac.iteration_max)
				stp->img[(int)x + (int)y * WIDTH] = 0;
			else
				stp->img[(int)x + (int)y * WIDTH] = ((i * 0xFF / stp->frac.iteration_max) << 16) + (i * 0xFF / stp->frac.iteration_max);
			x++;
		}
		y++;
	}
}

