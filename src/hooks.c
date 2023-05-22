/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:46:09 by dinunes-          #+#    #+#             */
/*   Updated: 2023/05/05 11:46:09 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	key_hook(int keycode, t_fractol *f)
{
	julia_keys(keycode, f);
	key_hook2(keycode, f);
	if (keycode == KEY_ONE)
		f->r += 50;
	else if (keycode == KEY_TWO)
		f->g += 50;
	else if (keycode == KEY_THREE)
		f->b += 50;
	else if (keycode == KEY_FOUR)
	{
		f->r = 100;
		f->g = 100;
		f->b = 100;
	}
	else if (keycode == KEY_ESC)
		end_fractol(f);
	else
		return (1);
	if (f)
		renderimg(f);
	return (0);
}

int	key_hook2(int keycode, t_fractol *f)
{
	if (keycode == KEY_W)
		move(f, 0.2, 'U');
	else if (keycode == KEY_A)
		move(f, 0.2, 'L');
	else if (keycode == KEY_S)
		move(f, 0.2, 'D');
	else if (keycode == KEY_D)
		move(f, 0.2, 'R');
	else
		return (1);
	if (f)
		renderimg(f);
	return (0);
}

int	julia_keys(int keycode, t_fractol *f)
{
	if (f->set == 2)
	{
		if (keycode == KEY_LEFT)
			f->kr -= 0.01;
		else if (keycode == KEY_RIGHT)
			f->kr += 0.01;
		if (f)
			renderimg(f);
	}
	return (0);
}

int	mouse_hook(int button, int x, int y, t_fractol *f)
{
	if (button == MOUSE_WHEEL_UP)
	{
		zoom(f, (double)x, (double)y, 1.5);
	}
	else if (button == MOUSE_WHEEL_DOWN)
	{
		zoom(f, (double)x, (double)y, 0.67);
	}
	else
		return (1);
	if (f)
		renderimg(f);
	return (0);
}