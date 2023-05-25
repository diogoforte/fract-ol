/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:27:17 by dinunes-          #+#    #+#             */
/*   Updated: 2023/05/05 10:27:17 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../mlx_linux/mlx.h"
# include "libft.h"
# include "keys.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>

/*  Dimensions	*/
# define WIDTH 1080
# define HEIGHT 1080

typedef struct s_fractol
{
	void		*mlx;
	void		*win;
	int			set;
	int			r;
	int			g;
	int			b;
	double		kr;
	double		ki;
	double		scale;
	double		min_r;
	double		max_r;
	double		min_i;
	double		max_i;
	int			max_iter;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}t_fractol;

void		help_msg(void);
void		init(t_fractol *f, char **av);
void		clean_exit(int exit_code, t_fractol *f);
void		handle_args(t_fractol *f, char **av);
void		handle_args2(t_fractol *f, char **av);
int			key_hook(int keycode, t_fractol *f);
void		my_mlx_pixel_put(t_fractol *f, int x, int y, int color);
void		renderimg(t_fractol *f);
int			create_trgb(int t, int r, int g, int b);
int			end_fractol(t_fractol *mlx);
void		clean_init(t_fractol *f);
int			handle_mouse_event(t_fractol *f, int button);
int			julia(t_fractol *f, double zr, double zi);
int			mandelbrot(t_fractol *f, double cr, double ci);
int			julia_keys(int keycode, t_fractol *f);
int			mouse_hook(int button, int x, int y, t_fractol *f);
void		zoom(t_fractol *f, double mouse_x,
				double mouse_y, double zoom_factor);
void		move(t_fractol *f, double distance, int direction);
int			key_hook2(int keycode, t_fractol *f);
void		pixelcolor(t_fractol *f, int x, int y, int color);
int			setselect(t_fractol *f, int x, int y);
int			tricorn(t_fractol *f, double cr, double ci);
int			celtic(t_fractol *f, double zr, double zi);
#endif