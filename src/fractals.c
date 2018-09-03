/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 16:43:00 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/03 19:45:19 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <math.h>

int		get_fractal_col(t_env *win, int x, int y)
{
	if (win->param->fr_id == FR_BATMAN)
		return (batman_col(win, x, y));
	if (win->param->fr_id == FR_MANDELBROT)
		return ((win->flags->man_4) ? mandelbrot_cuboid(win, x, y)
									: mandelbrot_col(win, x, y));
	return (0);
}
static int	if_сardioid(t_env *win, double pr, double pi)
{
	double		pr_pow;
	double		pi_pow;
	double		q;
	t_flags		*flags;

	if (!win
		|| !(flags = win->flags)
		|| flags->man_1 || flags->man_2 || flags->man_3)
		return (0);
	pr *= ((win->flags->man_6) ? -1 : 1);
	pr_pow = ((pr - 0.25) * (pr - 0.25));
	pi_pow = pi * pi;
	q = pr_pow + pi_pow;

	if ((pr + 1) * (pr + 1) + pi_pow < 0.0625
		|| (q * (q + (pr - 0.25)) < 0.25 * pi_pow))
		return (1);
	return (0);
}

int		mandel_break(t_env *win, t_cnb *c)
{
	if (pow_of(c->newR, 2) + pow_of(c->newI, 2) > 4)
		return (1);
	//win->param->color_step++;
	if (win->flags->man_5 && (c->newR > 0.5 || c->newR < -2.0))
		return (1);
	if (win->flags->man_5 && (c->newI > 0.8 || c->newI < -0.8))
		return (1);

	return (0);
}

int		mandelbrot_col(t_env *win, int x, int y)
{
	int		i;
	t_cnb	z;
	double	pr;
	double	pi;
	t_param *par;

	par = win->param;
	pr = par->ratio * (x - par->center_x) / par->zoom + par->offset_x;// (par->zoom + x_coeficien gives allusion)
	pi =			  (y - par->center_y) / par->zoom + par->offset_y;//

	i = -1;
	z.newR = 0;
	z.newI = 0;
	if (if_сardioid(win, pr, pi))
		return (0xffffff);
	while (++i < par->iter && i >= 0)
	{
		//		z.r = 0;
		//		z.i = 0;
		//		zrsqr = z.r * z.r;
		//		zisqr = z.i * z.i;
		//		while (zrsqr + zisqr <= 4.0)
		//		{
		//			z.i = square(z.r + z.i) – zrsqr – zisqr;
		//			z.i += c.i;
		//			z.r = zrsqr – zisqr + c.r;
		//			zrsqr = square(z.r);
		//			zisqr = square(z.i);
		//		}

		if (mandel_break(win, &z))
			break ;
		z.oldR = (win->flags->man_2) ? fabs(z.newR) : z.newR;
		z.oldI = (win->flags->man_3) ? fabs(z.newI) : z.newI;
		z.newR = z.oldR * z.oldR - z.oldI * z.oldI + pr
													 * ((win->flags->man_6) ? -1 : 1);
		z.newI = (2 * z.oldR * z.oldI + pi) * ((win->flags->man_1) ? -1 : 1);
	}
	return (get_color(win, i));
}

int		mandelbrot2_col(t_env *win, int x, int y)
{
	int		i;
	t_cnb	c;
	double	pr;
	double	pi;
	t_param *par;

	par = win->param;
	pr = par->ratio * (x - par->center_x) / par->zoom + par->offset_x;
	pi =			  (y - par->center_y) / par->zoom + par->offset_y;

	i = -1;
	c.newR = 0;
	c.newI = 0;
	if (if_сardioid(win, pr, pi)
		&& !win->flags->man_1 && !win->flags->man_2 && !win->flags->man_3)
		return (0);
	while (++i < par->iter && i >= 0)
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

int		batman_col(t_env *win, int x, int y)
{
	int		i;
	t_cnb	z;
	double	pr;
	double	pi;
	t_param *par;

	par = win->param;
	pr = par->ratio * (x - par->center_x) / (par->zoom);
	pi =			(y - par->center_y) / (par->zoom);

	i = -1;
	z.newR = 0;
	z.newI = 0;
	if (if_сardioid(win, pr, pi))
		return (0xffffff);
	while (++i < par->iter && i >= 0)
	{
		if (mandel_break(win, &z))
			break ;
		z.oldR = (win->flags->man_2) ? fabs(z.newR) : z.newR;
		z.oldI = (win->flags->man_3) ? fabs(z.newI) : z.newI;
		z.newR = (pow_of(z.oldR, 2) * pow_of(z.oldI, 2) + pr)
				 * ((win->flags->man_6) ? -1 : 1);
		z.newI = (2 * z.oldR * z.oldI + pi) * ((win->flags->man_1) ? -1 : 1);
	}
	return (get_color(win, i));
}

int		mandelbrot_cuboid(t_env *win, int x, int y)
{
	int		i;
	t_cnb	c;
	double	pr;
	double	pi;
	t_param *par;

	par = win->param;
	pr = par->ratio * (x - par->center_x) / par->zoom_x	+ par->offset_x;
	pi =			(y - par->center_y) / par->zoom_y + par->offset_y;
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
