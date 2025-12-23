/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkutlu <zkutlu@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 20:19:28 by zkutlu            #+#    #+#             */
/*   Updated: 2025/12/23 20:28:17 by zkutlu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* fractol.h */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <mlx.h>
# include "libft/libft.h"
# include <stdbool.h>
# define PX_X 800
# define PX_Y 600
# define MAX_ITER 100

typedef struct s_fractol
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
	int		type;
	int		max_iter;
	int		flag;
	double	escape2;
	double	zoom;
	double	shift_x;
	double	shift_y;
	double	z_re;
	double	z_im;
	double	c_re;
	double	c_im;
	int		color_mode;
	double	re_step;
	double	im_step;

	bool	lock_julia;
}	t_fractol;

void	control_alphabet(char **av);
int		color_from_iter(t_fractol *f, int iter);
double	ft_atof(const char *str);
void	init_fractol(t_fractol *f, char **av, int i);
int		mlx_setup(t_fractol *fract);
void	put_pixel(t_fractol *f, int x, int y, int color);
void	draw_fract(t_fractol *f, int i);
int		handle_mouse(int button, int x, int y, t_fractol *f);
int		listen_key(int key_code, t_fractol *fract);
int		prog_free(t_fractol *f);
int		is_valid_double(char *s);
void	error_exit(int code);
int		has_escaped(t_fractol *f);

#endif