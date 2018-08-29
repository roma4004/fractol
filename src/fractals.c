/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 16:43:00 by dromanic          #+#    #+#             */
/*   Updated: 2018/08/29 21:16:11 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <math.h>

int		get_fractal_col(t_win *win, int x, int y)
{
	if (win->param->fr_id == FR_MANDELBROT)
	{
		if (win->flags->man_4)
			return (mandelbrot_cuboid(win, x, y));
		else
			return (mandelbrot_col(win, x, y));
	}
	return (0);
}

int		if_сardioid(double pr, double pi)
{
	double		pr_pow;
	double		pi_pow;
	double		q;
	double		p;

	pr_pow = ((pr - 0.25) * (pr - 0.25));

	pi_pow = pi * pi;

	q = pr_pow + pi_pow;
	p = sqrt(pr_pow + pi_pow);

//	if (pr < p - 2 * (p * p) + 0.25)
//	if (q * (q + (pr - 0.25)) < pow_of(0.25 * pi, 2)
//	|| (pow_of(pr + 1, 2) + pi_pow < 0.0325))
//		return (1);

	//if (q * (q + (pr - 0.25)) < 0.25 * pow_of(pi, 2))
	if ((pr < p - 2.5 * pow(p, 2) + 0.25)
	|| (pow_of(pr + 1, 2) + pi_pow < 0.0625))
		return (1);

	//if	((q * (q + (pr - 0.25)) < (pi * pi) / 4) ||
	//	(pr * pr + 2 * pr + 1 + pi * pi < 0.0225))
	//	return (1);
	return (0);
}

int		mandel_break(t_win *win, t_cnb *c)
{
	if (pow_of(c->newR, 2) + pow_of(c->newI, 2) > 4)
		return (1);
	if (win->flags->man_5 && (c->newR > 0.5 || c->newR < -2.0))
		return (1);
	if (win->flags->man_5 && (c->newI > 0.8 || c->newI < -0.8))
		return (1);

	return (0);
}

int		mandelbrot_col(t_win *win, int x, int y)
{
	int		i;
	t_cnb	c;
	double	pr;
	double	pi;
	t_param *par;

	par = win->param;
	pr = 1.5 * (x - par->centr_x) / (0.5 * par->zoom_x) + par->offset_x;
	pi =       (y - par->centr_y) / (0.5 * par->zoom_y) + par->offset_y;

	//pr = x / WIN_WIDTH * (1.8 * 2) + 1.5 - 1.8 - 0.75 - 1.8;
	//pi = y / WIN_HEIGHT * (1.44 * 2) + 1.2 - 1.44 - 1.44;
	i = -1;
	c.newR = 0;
	c.newI = 0;

	//if (check_mndl(((pr * pr - 0.5 * pr + 0.825) + pi * pi), pr, pi))
//	if (if_сardioid(pr, pi))
//		return (0xffffff);
	while (++i < par->iter && i >= 0)//&& (x*x + y*y < 2*2))
	{
		if (mandel_break(win, &c))
			break ;
		c.oldR = (win->flags->man_2) ? fabs(c.newR) : c.newR;
		c.oldI = (win->flags->man_3) ? fabs(c.newI) : c.newI;
		c.newR = pow_of(c.oldR, 2) - pow_of(c.oldI, 2) + pr
											* ((win->flags->man_6) ? -1 : 1);
		c.newI = (2 * c.oldR * c.oldI + pi) * ((win->flags->man_1) ? -1 : 1);
//		c.newR = pow_of(c.oldR, 2) - 2 * pow_of(c.oldI, 2) + pr
//											* ((win->flags->man_6) ? -1 : 1);
//		c.newI = (2 * c.oldR * c.oldI + pi) * ((win->flags->man_1) ? -1 : 1);
	}
	return (get_color(win, i));
}

int		mandelbrot2_col(t_win *win, int x, int y)
{
	int		i;
	t_cnb	c;
	double	pr;
	double	pi;
	t_param *par;

	par = win->param;
	pr = 1.5 * (x - par->centr_x) / par->zoom_x + par->offset_x;
	pi =       (y - par->centr_y) / par->zoom_y + par->offset_y;

	//pr = x / WIN_WIDTH * (1.8 * 2) + 1.5 - 1.8 - 0.75 - 1.8;
	//pi = y / WIN_HEIGHT * (1.44 * 2) + 1.2 - 1.44 - 1.44;
	i = -1;
	c.newR = 0;
	c.newI = 0;

	//if (check_mndl(((pr * pr - 0.5 * pr + 0.825) + pi * pi), pr, pi))
//	if (if_сardioid(pr, pi))
//		return (0xffffff);
	while (++i < par->iter && i >= 0)//&& (x*x + y*y < 2*2))
	{
		if (mandel_break(win, &c))
			break ;
		c.oldR = (win->flags->man_2) ? fabs(c.newR) : c.newR;
		c.oldI = (win->flags->man_3) ? fabs(c.newI) : c.newI;
		c.newR = pow_of(c.oldR, 2) - 2 * pow_of(c.oldI, 2) + pr
											* ((win->flags->man_6) ? -1 : 1);
		c.newI = (2 * c.oldR * c.oldI + pi) * ((win->flags->man_1) ? -1 : 1);
	}
	return (get_color(win, i));
}

int		batman_col(t_win *win, int x, int y)
{
	int		i;
	t_cnb	c;
	double	pr;
	double	pi;
	t_param *par;

	par = win->param;
	pr = 1.5 * (x - par->centr_x) / par->zoom_x + par->offset_x;
	pi =       (y - par->centr_y) / par->zoom_y + par->offset_y;

	i = -1;
	c.newR = 0;
	c.newI = 0;

	while (++i < par->iter && i >= 0)//&& (x*x + y*y < 2*2))
	{
		if (mandel_break(win, &c))
			break ;
		c.oldR = (win->flags->man_2) ? fabs(c.newR) : c.newR;
		c.oldI = (win->flags->man_3) ? fabs(c.newI) : c.newI;
		c.newR = pow_of(c.oldR, 2) * pow_of(c.oldI, 2) + pr
											* ((win->flags->man_6) ? -1 : 1);
		c.newI = (2 * c.oldR * c.oldI + pi) * ((win->flags->man_1) ? -1 : 1);
	}
	return (get_color(win, i));
}

int		mandelbrot_cuboid(t_win *win, int x, int y)
{
	int		i;
	t_cnb	c;
	double	pr;
	double	pi;
	t_param *par;

	par = win->param;
	pr = win->img->ratio * (x - par->centr_x) / par->zoom_x
		+ par->offset_x;
	pi = (y - par->centr_y) / par->zoom_y + par->offset_y;
	i = -1;
	c.newR = 0;
	c.newI = 0;
	while (++i < win->param->iter)
	{
		c.oldR = (win->flags->man_2) ? fabs(c.newR) : c.newR;
		c.oldI = (win->flags->man_3) ? fabs(c.newI) : c.newI;
		c.newR = pow_of(c.oldR, 3) - 3 * c.oldR * pow_of(c.oldI, 2) + pr
											* ((win->flags->man_6) ? -1 : 1);
		c.newI = (3 * pow_of(c.oldR, 2) * c.oldI - pow_of(c.oldI, 3) + pi)
											* ((win->flags->man_1) ? -1 : 1);
		if ((pow_of(c.newR, 2) + pow_of(c.newI, 2)) > 4)
			break;
	}
	return (get_color(win, i));
}

