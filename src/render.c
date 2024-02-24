/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:10:21 by dinunes-          #+#    #+#             */
/*   Updated: 2023/05/05 12:10:21 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	my_mlx_pixel_put(t_fractol *f, int x, int y, int color)
{
	char	*dst;

	dst = f->addr + (y * f->line_length + x * (f->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void *renderimg_thread(void *arg)
{
    t_thread_data *data = (t_thread_data *)arg;
    t_fractol *f = data->f;
    int x, y;

    for (y = data->start_y; y < data->end_y; y++)
    {
        for (x = 0; x < WIDTH; x++)
        {
            pixelcolor(f, x, y, setselect(f, x, y));
        }
    }

    return NULL;
}

void renderimg(t_fractol *f)
{
    pthread_t threads[NUM_THREADS];
    t_thread_data thread_data[NUM_THREADS];
    int i;

    for (i = 0; i < NUM_THREADS; i++)
    {
        thread_data[i].f = f;
        thread_data[i].start_y = i * HEIGHT / NUM_THREADS;
        thread_data[i].end_y = (i + 1) * HEIGHT / NUM_THREADS;

        pthread_create(&threads[i], NULL, renderimg_thread, &thread_data[i]);
    }

    for (i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
    ft_putstr_fd("Image rendered.\n", 2);
}

int	setselect(t_fractol *f, int x, int y)
{
	int		color;
	double	pr;
	double	pi;

	color = 0;
	pr = f->min_r + (double)x * (f->max_r - f->min_r) / WIDTH;
	pi = f->min_i + (double)y * (f->max_i - f->min_i) / HEIGHT;
	if (f->set == 1)
		color = mandelbrot(f, pr, pi);
	else if (f->set == 2)
		color = julia(f, pr, pi);
	else if (f->set == 3)
		color = tricorn(f, pr, pi);
	else if (f->set == 4)
		color = celtic(f, pr, pi);
	return (color);
}

void	pixelcolor(t_fractol *f, int x, int y, int color)
{
	if (color == f->max_iter)
		color = 0;
	else
		color = create_trgb(0, f->r * color / f->max_iter, f->g * color
				/ f->max_iter, f->b * color / f->max_iter);
	my_mlx_pixel_put(f, x, y, color);
}
