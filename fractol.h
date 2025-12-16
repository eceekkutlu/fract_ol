/* fractol.h */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <mlx.h>
# include "libft/libft.h"
# include <stdbool.h>
#define PX_X 800
#define PX_Y 600
#define MAX_ITER 100



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
	double	escape2;
	double	zoom;
	double	shift_x;
	double	shift_y;
	double	z_re;
	double	z_im;
	double	c_re;
	double	c_im;
	int		color_mode;

	bool	lock_julia;
}	t_fractol;

#endif
