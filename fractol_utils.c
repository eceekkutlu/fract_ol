/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkutlu <zkutlu@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 20:21:59 by zkutlu            #+#    #+#             */
/*   Updated: 2025/12/23 20:22:28 by zkutlu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	listen_key(int key_code, t_fractol *fract)
{
	double	move;

	move = 0.5 / fract->zoom;
	if (key_code == 65307)
		prog_free(fract);
	else
		return (0);
	if (fract->flag == 0)
		draw_fract(fract, 0);
	else if (fract->flag == 1)
		draw_fract(fract, 1);
	return (0);
}

int	handle_mouse(int button, int x, int y, t_fractol *f)
{
	double	zoom_factor;

	(void)x;
	(void)y;
	zoom_factor = 1.2;
	if (button == 4)
		f->zoom *= zoom_factor;
	else if (button == 5)
		f->zoom /= zoom_factor;
	else
		return (0);
	if (f->flag == 0)
		draw_fract(f, 0);
	else if (f->flag == 1)
		draw_fract(f, 1);
	return (0);
}

int	prog_free(t_fractol *f)
{
	mlx_destroy_image(f->mlx, f->img);
	mlx_destroy_window(f->mlx, f->win);
	mlx_destroy_display(f->mlx);
	free(f->mlx);
	exit(0);
}
