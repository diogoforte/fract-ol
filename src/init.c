/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 21:19:41 by dinunes-          #+#    #+#             */
/*   Updated: 2023/05/21 21:19:41 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init(t_fractol *f, char **av)
{
	f->mlx = mlx_init();
	if (!f->mlx)
	{
		ft_putstr_fd("MLX: \033[0;91merror\033[0;0m connecting to mlx.", 2);
		clean_exit(1, f);
	}
	f->win = mlx_new_window(f->mlx, WIDTH, HEIGHT, "fract-ol");
	if (!f->win)
	{
		ft_putstr_fd("MLX: \033[0;91merror\033[0;0m creating window.", 2);
		clean_exit(1, f);
	}
	f->img = mlx_new_image(f->mlx, WIDTH, HEIGHT);
	if (!f->img)
	{
		ft_putstr_fd("MLX: \033[0;91merror\033[0;0m creating image.", 2);
		clean_exit(1, f);
	}
	f->addr = mlx_get_data_addr(f->img, &(f->bits_per_pixel),
			&(f->line_length), &(f->endian));
	clean_init(f);
	if (av[2] && av[3] && f->set == 2)
		handle_args2(f, av);
}

void	clean_init(t_fractol *f)
{
	f->kr = -0.7;
	f->ki = 0.27015;
	f->scale = 1;
	f->min_r = -2;
	f->max_r = 2;
	f->min_i = -2;
	f->max_i = 2;
	f->r = 100;
	f->g = 100;
	f->b = 300;
	f->max_iter = 100;
}

void	handle_args(t_fractol *f, char **av)
{
	int	i;

	i = 0;
	while (av[1][i])
	{
		av[1][i] = ft_tolower(av[1][i]);
		i++;
	}
	if (!ft_strncmp(av[1], "mandelbrot", 11) && !av[2])
		f->set = 1;
	else if (!ft_strncmp(av[1], "julia", 6) && (!av[2] || !av[4]))
		f->set = 2;
	else if (!ft_strncmp(av[1], "tricorn", 8) && !av[2])
		f->set = 3;
	else if (!ft_strncmp(av[1], "celtic", 7) && !av[2])
		f->set = 4;
	else
	{
		ft_putstr_fd("That fractal is \033[0;91mnot \033[0;00mavailable.\n", 2);
		help_msg();
	}
}

void	handle_args2(t_fractol *f, char **av)
{
	f->kr = ft_atoi(av[2]);
	f->ki = ft_atoi(av[3]);
	if (f->kr > 2 || f->kr < -2)
		end_fractol(f);
	if (f->ki > 2 || f->ki < -2)
		end_fractol(f);
}

void	help_msg(void)
{
	ft_putstr_fd("Available fractal sets:\n", 2);
	ft_putstr_fd("  -> \033[0;91mMandelbrot\033[0;0m\n", 2);
	ft_putstr_fd("  -> \033[0;91mJulia\033[0;0m\n", 2);
	ft_putstr_fd("  -> \033[0;91mTricorn\033[0;0m\n", 2);
	ft_putstr_fd("  -> \033[0;91mCeltic\033[0;0m\n", 2);
	ft_putstr_fd("Run the program like:\n", 2);
	ft_putstr_fd("  ./fractol \033[0;91m(fractal set)\x1B[0m\n", 2);
	ft_putstr_fd("Move the image:\n", 2);
	ft_putstr_fd("  -> arrow \033[0;91mUP/DOWN/LEFT/RIGHT\x1B[0m\n", 2);
	ft_putstr_fd("Increase/Decrease iterations:\n", 2);
	ft_putstr_fd("  -> \033[0;91mPLUS/MINUS\x1B[0m\n", 2);
	ft_putstr_fd("Change RGB values:\n", 2);
	ft_putstr_fd("  -> \033[0;91m1 2 3\x1B[0m\n", 2);
	ft_putstr_fd("Reset RGB values:\n", 2);
	ft_putstr_fd("  -> \033[0;91m4\x1B[0m\n", 2);
	ft_putstr_fd("Julia set commands:\n", 2);
	ft_putstr_fd("  ./fractol Julia", 2);
	ft_putstr_fd("\033[0;91m (REAL) (IMAGINARY)\033[0;00m.\n", 2);
	ft_putstr_fd("Move between Julia sets:\n", 2);
	ft_putstr_fd("  -> \033[0;91mWASD\x1B[0m\n", 2);
	exit(1);
}
