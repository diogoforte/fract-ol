/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:52:30 by dinunes-          #+#    #+#             */
/*   Updated: 2023/05/22 12:52:30 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int tricorn(t_fractol *f, double cr, double ci)
{
   int     n;
   double  zr;
   double  zi;
   double  tmp;

   zr = 0;
   zi = 0;
   n = 0;
   while (n < f->max_iter)
   {
       if ((zr * zr + zi * zi) > 4.0)
           break ;
       tmp = zr * zr - zi * zi + cr;
       zi = -2.0 * zr * zi + ci;
       zr = tmp;
       n++;
   }
   return (n);
}