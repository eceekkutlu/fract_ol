#include "fractol.h"
#include <stdlib.h>
#include <math.h>    // istersen sadece renk için vs, şart değil

/* --------------------------------------------------------- */
/*  BASIC PIXEL PUT                                           */
/* --------------------------------------------------------- */
static void	put_pixel(t_fractol *f, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= f->width || y < 0 || y >= f->height)
		return ;
	dst = f->addr + (y * f->line_len + x * (f->bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

/* --------------------------------------------------------- */
/*  INIT                                                      */
/* --------------------------------------------------------- */
void	init_fractol(t_fractol *f)
{
	f->width = 800;
	f->height = 600;

	f->zoom = 1.0;
	f->shift_x = 0.0;
	f->shift_y = 0.0;

	f->escape2 = 4.0;     // |z|>2 => re^2+im^2>4
	f->max_iter = 100;

	f->color_mode = 0;
	f->lock_julia = false;

	f->z_re = 0.0;
	f->z_im = 0.0;
	f->c_re = 0.0;
	f->c_im = 0.0;
}

/* --------------------------------------------------------- */
/*  PIXEL -> COMPLEX c                                        */
/* --------------------------------------------------------- */
static void	calculate_c(t_fractol *f, int px, int py)
{
	const double	max_x = 1.0;
	const double	min_x = -2.0;
	const double	max_y = 1.5;
	const double	min_y = -1.5;

	double	re_step;
	double	im_step;

	re_step = (max_x - min_x) / (double)f->width;
	im_step = (max_y - min_y) / (double)f->height;

	f->c_re = (min_x + px * re_step) / f->zoom + f->shift_x;
	f->c_im = (max_y - py * im_step) / f->zoom + f->shift_y;
}

/* --------------------------------------------------------- */
/*  MANDELBROT z0                                             */
/* --------------------------------------------------------- */
static void	mandel_init(t_fractol *f)
{
	f->z_re = 0.0;
	f->z_im = 0.0;
}

/* --------------------------------------------------------- */
/*  ESCAPE CHECK                                              */
/* --------------------------------------------------------- */
static int	has_escaped(t_fractol *f)
{
	return (f->z_re * f->z_re + f->z_im * f->z_im > f->escape2);
}

/* --------------------------------------------------------- */
/*  ONE ITERATION: z = z^2 + c                                */
/* --------------------------------------------------------- */
static void	mandel_step(t_fractol *f)
{
	double	new_re;
	double	new_im;

	new_re = f->z_re * f->z_re - f->z_im * f->z_im + f->c_re;
	new_im = 2.0 * f->z_re * f->z_im + f->c_im;
	f->z_re = new_re;
	f->z_im = new_im;
}

/* --------------------------------------------------------- */
/*  ITERATE AND RETURN ITER COUNT                             */
/* --------------------------------------------------------- */
static int	mandel_iter(t_fractol *f)
{
	int	i;

	i = 0;
	while (i < f->max_iter)
	{
		if (has_escaped(f))
			break ;
		mandel_step(f);
		i++;
	}
	return (i);
}

/* --------------------------------------------------------- */
/*  SIMPLE COLOR                                              */
/* --------------------------------------------------------- */
static int	color_from_iter(t_fractol *f, int iter)
{
	if (iter >= f->max_iter)
		return (0x000000); // set içi: siyah

	// basit bir gradient
	return (0x002244 + iter * 0x000A0A);
}

/* --------------------------------------------------------- */
/*  DRAW MANDELBROT                                           */
/* --------------------------------------------------------- */
static void	draw_mandelbrot(t_fractol *f)
{
	int	x;
	int	y;
	int	iter;
	int	color;

	y = 0;
	while (y < f->height)
	{
		x = 0;
		while (x < f->width)
		{
			calculate_c(f, x, y);
			mandel_init(f);
			iter = mandel_iter(f);
			color = color_from_iter(f, iter);
			put_pixel(f, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
}

/* --------------------------------------------------------- */
/*  MAIN                                                      */
/* --------------------------------------------------------- */
int	main(int ac, char **av)
{
	t_fractol	fract;

	if (ac != 2)
		return (1);

	// 42'de genelde küçük harf kullanılır: "mandelbrot"
	// ft_strncmp eşitse 0 döner -> şart ona göre olmalı
	if (ft_strncmp(av[1], "mandelbrot", 10) != 0)
		return (1);

	init_fractol(&fract);

	fract.mlx = mlx_init();
	if (!fract.mlx)
		return (1);

	fract.win = mlx_new_window(fract.mlx, fract.width, fract.height, "fract-ol");
	if (!fract.win)
		return (1);

	fract.img = mlx_new_image(fract.mlx, fract.width, fract.height);
	if (!fract.img)
		return (1);

	fract.addr = mlx_get_data_addr(fract.img, &fract.bpp, &fract.line_len, &fract.endian);
	if (!fract.addr)
		return (1);

	draw_mandelbrot(&fract);

	mlx_loop(fract.mlx);
	return (0);
}
