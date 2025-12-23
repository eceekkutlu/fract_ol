/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkutlu <zkutlu@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 20:19:16 by zkutlu            #+#    #+#             */
/*   Updated: 2025/12/23 20:29:23 by zkutlu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	put_pixel(t_fractol *f, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= f->width || y < 0 || y >= f->height)
		return ;
	dst = f->addr + (y * f->line_len + x * (f->bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

void	init_fractol(t_fractol *f, char **av, int i)
{
	f->width = 800;
	f->height = 600;
	f->zoom = 1.0;
	f->shift_x = 0.0;
	f->shift_y = 0.0;
	f->escape2 = 4.0;
	f->max_iter = 100;
	f->color_mode = 0;
	if (i == 0)
	{
		f->flag = 0;
		f->c_re = 0.0;
		f->c_im = 0.0;
	}
	else if (i == 1)
	{
		f->flag = 1;
		f->c_re = ft_atof(av[2]);
		f->c_im = -ft_atof(av[3]);
	}
	f->z_re = 0.0;
	f->z_im = 0.0;
}

static void	calculate_c(t_fractol *f, int px, int py, int i)
{
	const double	max_x = 1.0;
	const double	min_x = -2.0;
	const double	max_y = 1.5;
	const double	min_y = -1.5;

	f->re_step = (max_x - min_x) / (double)f->width;
	f->im_step = (max_y - min_y) / (double)f->height;
	if (i == 0)
	{
		f->c_re = (min_x + px * re_step) / f->zoom + f->shift_x;
		f->c_im = (max_y - py * im_step) / f->zoom + f->shift_y;
		f->z_re = 0.0;
		f->z_im = 0.0;
	}
	if (i == 1)
	{
		f->z_re = (min_x + px * re_step) / f->zoom + f->shift_x;
		f->z_im = (max_y - py * im_step) / f->zoom + f->shift_y;
	}
}

static void	fract_step(t_fractol *f)
{
	double	new_re;
	double	new_im;

	new_re = f->z_re * f->z_re - f->z_im * f->z_im + f->c_re;
	new_im = 2.0 * f->z_re * f->z_im + f->c_im;
	f->z_re = new_re;
	f->z_im = new_im;
}

static int	fract_iter(t_fractol *f)
{
	int	i;

	i = 0;
	while (i < f->max_iter)
	{
		if (has_escaped(f))
			break ;
		fract_step(f);
		i++;
	}
	return (i);
}
void	draw_fract(t_fractol *f, int i)
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
			calculate_c(f, x, y, i);
			iter = fract_iter(f);
			color = color_from_iter(f, iter);
			put_pixel(f, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
}

int	mlx_setup(t_fractol *fract)
{
	fract->mlx = mlx_init();
	if (!fract->mlx)
		return (1);
	fract->win = mlx_new_window(fract->mlx, fract->width, fract->height,
			"fract-ol");
	if (!fract->win)
		return (1);
	fract->img = mlx_new_image(fract->mlx, fract->width, fract->height);
	if (!fract->img)
		return (1);
	fract->addr = mlx_get_data_addr(fract->img, &fract->bpp, &fract->line_len,
			&fract->endian);
	if (!fract->addr)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_fractol	fract;

	if (ac < 2)
		error_exit(1);
	if (ft_strncmp(av[1], "mandelbrot", 11) == 0)
		init_fractol(&fract, av, 0);
	else if (ft_strncmp(av[1], "julia", 6) == 0)
	{
		if (ac != 4)
			error_exit(3);
		if (!is_valid_double(av[2]) || !is_valid_double(av[3]))
			error_exit(3);
		init_fractol(&fract, av, 1);
	}
	else
		error_exit(2);
	if (mlx_setup(&fract))
		error_exit(5);
	draw_fract(&fract, fract.flag);
	mlx_key_hook(fract.win, listen_key, &fract);
	mlx_mouse_hook(fract.win, handle_mouse, &fract);
	mlx_hook(fract.win, 17, 0, prog_free, &fract);
	mlx_loop(fract.mlx);
	return (0);
}
