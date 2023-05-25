/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 07:32:20 by dinunes-          #+#    #+#             */
/*   Updated: 2023/05/22 07:32:20 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zoom(t_fractol *f, double mouse_x, double mouse_y, double zoom_factor)
{
	double	interpolation;
	double	mouse_r;
	double	mouse_i;

	interpolation = 1.0 / zoom_factor;
	mouse_r = f->min_r + mouse_x * (f->max_r - f->min_r) / WIDTH;
	mouse_i = f->min_i + mouse_y * (f->max_i - f->min_i) / HEIGHT;
	f->min_r = mouse_r - (mouse_r - f->min_r) * interpolation;
	f->min_i = mouse_i - (mouse_i - f->min_i) * interpolation;
	f->max_r = mouse_r + (f->max_r - mouse_r) * interpolation;
	f->max_i = mouse_i + (f->max_i - mouse_i) * interpolation;
}

void	move(t_fractol *f, double distance, int direction)
{
	double	center_r;
	double	center_i;

	center_r = f->max_r - f->min_r;
	center_i = f->max_i - f->min_i;
	if (direction == 4)
	{
		f->min_r += center_r * distance;
		f->max_r += center_r * distance;
	}
	else if (direction == 3)
	{
		f->min_r -= center_r * distance;
		f->max_r -= center_r * distance;
	}
	else if (direction == 2)
	{
		f->min_i -= center_i * distance;
		f->max_i -= center_i * distance;
	}
	else if (direction == 1)
	{
		f->min_i += center_i * distance;
		f->max_i += center_i * distance;
	}
}
