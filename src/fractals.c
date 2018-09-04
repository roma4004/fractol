/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 16:43:00 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/04 17:52:15 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <math.h>

int		get_fractal_col(t_env *win, int x, int y)
{
	if (win->param->fr_id == FR_BATMAN)
		return (batman_col(win, x, y));
	if (win->param->fr_id == FR_MANDELBROT)
		return ((win->flags->n4) ? mandelbrot_cuboid(win, x, y)
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
		|| flags->n1 || flags->n2 || flags->n3 || flags->n7)// || flags->n8)
		return (0);
	pr_pow = ((pr - 0.25) * (pr - 0.25));
	pi_pow = pi * pi;
	q = pr_pow + pi_pow;

	if ((pr + 1) * (pr + 1) + pi_pow < 0.0625
		|| (q * (q + (pr - 0.25)) < 0.25 * pi_pow))
		return (1);
	return (0);
}

int		mandel_break(t_env *win, t_cnb *z)
{
	if ((z->sqR = pow2(z->R, 2)) + (z->sqI = pow2(z->I, 2)) > 4)
		return (1);
	//win->param->color_step++;
	if (win->flags->n5 && (z->R > 0.5 || z->R < -2.0))
		return (1);
	if (win->flags->n5 && (z->I > 0.8 || z->I < -0.8))
		return (1);

	return (0);
}

int		mandelbrot_col(t_env *win, int x, int y)
{
	t_cnb	z;
	t_param	*p;
	t_flags	*f;

	p = win->param;
	f = win->flags;
	z.cR = (p->ratio * (x - p->center_x) / p->zoom + p->offset_x)
			* ((f->n6) ? -1 : 1); // (p->zoom + x_coeficien gives allusion)
	z.cI = (y - p->center_y) / p->zoom + p->offset_y;
	if (!(z.j = -1) || (f->Y && if_сardioid(win, z.cR, z.cI)))
		return ((f->W) ? 0xffffff : 0x0);
	z.R = (f->Q) ? z.cR : 0;
	z.I = (f->E) ? z.cI : 0;
	while (++z.j < p->iter && !mandel_break(win, &z))
	{
		z.I = (pow2(z.R + z.I, 2) - z.sqR - z.sqI + z.cI) * ((f->n1) ? -1 : 1);
		z.I = (f->n2) ? fabs(z.I) : z.I;
		z.I *= (f->n7) ? -1 : 1;
		z.R = (f->n3) ? fabs(z.sqR - z.sqI + z.cR) : z.sqR - z.sqI + z.cR;
	}
	return (get_color(win, z.j));
//	while (++I < p->iter && I >= 0)
//	{
//		if (mandel_break(win, &z))
//			break ;
//		z.oldR = (f->n2) ? fabs(z.R) : z.R;
//		z.oldI = (f->n3) ? fabs(z.I) : z.I;
//		z.R = z.oldR * z.oldR - z.oldI * z.oldI + pr
//													 * ((f->n6) ? -1 : 1);
//		z.I = (2 * z.oldR * z.oldI + pi) * ((f->n1) ? -1 : 1);
//	}

}

//int		mandelbrot2_col(t_env *win, int x, int y)
//{
//	int		i;
//	t_cnb	c;
//	double	pr;
//	double	pi;
//	t_param	*par;
//
//	par = win->param;
//	pr = par->ratio * (x - par->center_x) / par->zoom + par->offset_x;
//	pi =			  (y - par->center_y) / par->zoom + par->offset_y;
//
//	i = -1;
//	c.R = 0;
//	c.I = 0;
//	if (if_сardioid(win, pr, pi)
//		&& !win->flags->n1 && !win->flags->n2 && !win->flags->n3)
//		return (0);
//	while (++i < par->iter && i >= 0)
//	{
//		if (mandel_break(win, &c))
//			break ;
//		c.oldR = (win->flags->n2) ? fabs(c.R) : c.R;
//		c.oldI = (win->flags->n3) ? fabs(c.I) : c.I;
//		c.R = pow_of(c.oldR, 2) - 2 * pow2(c.oldI, 2) + pr
//															 * ((win->flags->n6) ? -1 : 1);
//		c.I = (2 * c.oldR * c.oldI + pi) * ((win->flags->n1) ? -1 : 1);
//	}
//	return (get_color(win, i));
//}

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
	z.R = 0;
	z.I = 0;
	//if (if_сardioid(win, pr, pi))
	//	return (0xffffff);
	while (++i < par->iter && i >= 0)
	{
		if (mandel_break(win, &z))
			break ;
		z.oldR = (win->flags->n2) ? fabs(z.R) : z.R;
		z.oldI = (win->flags->n3) ? fabs(z.I) : z.I;
		z.R = (pow2(z.oldR, 2) * pow2(z.oldI, 2) + pr)
				 * ((win->flags->n6) ? -1 : 1);
		z.I = (2 * z.oldR * z.oldI + pi) * ((win->flags->n1) ? -1 : 1);
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
	c.R = 0;
	c.I = 0;
	while (++i < win->param->iter)
	{
		c.oldR = (win->flags->n2) ? fabs(c.R) : c.R;
		c.oldI = (win->flags->n3) ? fabs(c.I) : c.I;
		c.R = pow2(c.oldR, 3) - 3 * c.oldR * pow2(c.oldI, 2) + pr
																	  * ((win->flags->n6) ? -1 : 1);
		c.I = (3 * pow2(c.oldR, 2) * c.oldI - pow2(c.oldI, 3) + pi)
				 * ((win->flags->n1) ? -1 : 1);
		if ((pow2(c.R, 2) + pow2(c.I, 2)) > 4)
			break;
	}
	return (get_color(win, i));
}
