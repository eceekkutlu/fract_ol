/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_control.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkutlu <zkutlu@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 20:19:19 by zkutlu            #+#    #+#             */
/*   Updated: 2025/12/23 20:23:50 by zkutlu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	is_valid_double(char *s)
{
	int	i;
	int	dot_count;

	i = 0;
	dot_count = 0;
	if (!s || !s[0])
		return (0);
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i])
	{
		if (s[i] == '.')
		{
			dot_count++;
			if (dot_count > 1)
				return (0);
		}
		else if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	skip_space_sign(const char **s, int *sign)
{
	while (**s == 32 || (**s <= 13 && **s >= 9))
		(*s)++;
	*sign = 1;
	if (**s == '-' || **s == '+')
	{
		if (**s == '-')
			*sign = -1;
		(*s)++;
	}
	if (**s == '.')
		error_exit(1);
}

double	ft_atof(const char *str)
{
	int		sign;
	int		result;
	double	zero_next;
	int		i;

	skip_space_sign(&str, &sign);
	i = 1;
	zero_next = 0.0;
	result = 0;
	while (*str <= '9' && *str >= '0')
	{
		result = result * 10 + (*str - 48);
		str++;
	}
	if (*str == '.')
		str++;
	while (*str)
	{
		zero_next = zero_next * 10 + (*str - 48);
		i *= 10;
		str++;
	}
	return ((result + zero_next / i) * sign);
}

int	color_from_iter(t_fractol *f, int iter)
{
	if (iter >= f->max_iter)
		return (0x000000);
	return (0x002244 + iter * 0x000A0A);
}

void	error_exit(int code)
{
	if (code == 1)
		write(2, "Usage: ./fractol mandelbrot | julia <re> <im>\n", 47);
	else if (code == 2)
		write(2, "Error: unknown fractal\n", 24);
	else if (code == 3)
		write(2, "Error: invalid Julia parameters\n", 33);
	else if (code == 4)
		write(2, "Error: mlx init failed\n", 24);
	else if (code == 5)
		write(2, "Error: mlx setup failed\n", 25);
	exit(1);
}

int	has_escaped(t_fractol *f)
{
	return (f->z_re * f->z_re + f->z_im * f->z_im > f->escape2);
}
