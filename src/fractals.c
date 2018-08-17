/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 16:43:00 by dromanic          #+#    #+#             */
/*   Updated: 2018/08/17 17:22:04 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		get_fractal_point(t_win *win, t_coords *indexs)
{
	if (win->param->fr_id == FR_MANDELBROT)
	{
		if (win->flags->man_4)
			return (mandelbrot_cuboid(win, indexs));
		else
			return (mandelbrot(win, indexs));
	}
	return 0;
}

int		mandelbrot(t_win *win, t_coords *indexs)
{
	int		i;
	t_cnb	c;
	double	pr;
	double	pi;

	pr    = win->img->ratio * (indexs->x - win->param->centr_x)
							/ win->param->zoom_x
							+ win->param->offset_x;
	pi    =       (indexs->y - win->param->centr_y)
							/ win->param->zoom_y
							+ win->param->offset_y;
	i = -1;
	c.newR = 0;
	c.newI = 0;
	while (++i < win->param->iter)
	{
		c.oldR = (win->flags->man_2) ? fabs(c.newR) : c.newR;
		c.oldI = (win->flags->man_3) ? fabs(c.newI) : c.newI;
		//the actual iteration, the real and imaginary part are calculated
		c.newR = pow_of(c.oldR, 2) - 2 * pow_of(c.oldI, 2) + pr;
		c.newI = (2 * c.oldR * c.oldI + pi) * ((win->flags->man_1) ? -1 :
											   1);
		if ((pow_of(c.newR, 2) + pow_of(c.newI, 2)) > 4)
			break;
	}
	return (i);
}

int		mandelbrot_cuboid(t_win *win, t_coords *indexs)
{
	int		i;
	t_cnb	c;
	double	pr;
	double	pi;

	pr    = 1.5 * (indexs->x - win->param->centr_x)
								/ win->param->zoom_x
								+ win->param->offset_x;
	pi    =       (indexs->y - win->param->centr_y)
				  				/ win->param->zoom_y
								+ win->param->offset_y;
	i = -1;
	c.newR = 0;
	c.newI = 0;
	while (++i < win->param->iter)
	{
		c.oldR = (win->flags->man_2) ? fabs(c.newR) : c.newR;
		c.oldI = (win->flags->man_3) ? fabs(c.newI) : c.newI;
		//the actual iteration, the real and imaginary part are calculated
		c.newR =      pow_of(c.oldR, 3) - 3 * c.oldR * pow_of(c.oldI, 2) + pr;
		c.newI = (3 * pow_of(c.oldR, 2)     * c.oldI - pow_of(c.oldI, 3) + pi)
											* ((win->flags->man_1) ? -1 : 1);
		if ((pow_of(c.newR, 2) + pow_of(c.newI, 2)) > 4)
			break;
	}
	return (i);
}

