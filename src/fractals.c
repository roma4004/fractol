/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 16:43:00 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/08 20:51:19 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <math.h>

int		get_fractal_col(t_env *win, int x, int y)
{
	if (win->param->fr_id == FR_JULIA)
		return (julia_col(win, x, y));
	if (win->param->fr_id == FR_BATMAN)
		return (batman_col(win, x, y));
	if (win->param->fr_id == FR_MANDELBROT)
		return (mandelbrot_col(win, x, y));
	if (win->param->fr_id == FR_MANDELBROT_CUBOID)
		return (mandelbrot_cuboid(win, x, y));
	return (0);
}
static int	if_сardioid(t_env *win, double pr, double pi)
{
	double		pr_pow;
	double		pi_pow;
	double		q;
	t_flags		*flags;

	if (!win
		|| win->param->fr_id == FR_JULIA
		|| !(flags = win->flags)
		|| flags->n1 || flags->n2 || flags->n3 || flags->n7)
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
	t_flags	*f;

	z->sqR = pow(z->R, 2);
	z->sqI = pow(z->I, 2);
	f = win->flags;
	if (f->n8 && z->sqR * z->sqI > win->param->spec1)
		return (1);
	if (f->n4 && z->sqR - z->sqI > win->param->spec1)
		return (1);
	if (!f->n8 && !f->n4 && z->sqR + z->sqI > win->param->spec1)
		return (1);
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
		* ((f->n6) ? -1 : 1);
	z.cI = ((y + p->seed_jI - p->center_y) / (p->zoom) + p->offset_y);
	if (!(z.iter = -1) || (f->Y && if_сardioid(win, z.cR, z.cI)))
		return ((f->W) ? 0xffffff : 0x0);
	z.R = (f->Q) ? z.cR : p->seed_jI;
	z.I = (f->E) ? z.cI : p->seed_jR;
	while (++z.iter < p->iter && !mandel_break(win, &z))
	{
		z.I = (pow2(z.R + z.I, 2) - z.sqR - z.sqI + z.cI) * ((f->n1) ? -1 : 1);
		z.I = (f->n2) ? fabs(z.I) : z.I;
		z.I *= (f->n7) ? -1 : 1;
		z.R = (f->n3) ? fabs(z.sqR - z.sqI + z.cR) : z.sqR - z.sqI + z.cR ;
	}
	return (get_color(win, z.iter));
}

int		julia_col(t_env *win, int x, int y)
{
	t_cnb z;
	t_param *p;
	t_flags *f;

	p = win->param;
	f = win->flags;
	z.cR = (p->ratio * (x - p->center_x) / p->zoom + p->offset_x)
		* ((f->n6) ? -1 : 1);
	z.cI = (y - p->center_y) / p->zoom + p->offset_y;
	if (!(z.iter = -1) || (f->Y && if_сardioid(win, z.cR, z.cI)))
		return ((f->W) ? 0xffffff : 0x0);
	z.R = (f->Q) ? 0 : z.cR;
	z.I = (f->E) ? 0 : z.cI;
	while (++z.iter < p->iter && !mandel_break(win, &z))
	{
		z.I = (pow2(z.R + z.I, 2) - z.sqR - z.sqI + p->seed_jI) * ((f->n1) ? -1 : 1);
		z.I = (f->n2) ? fabs(z.I) : z.I;
		z.I *= (f->n7) ? -1 : 1;
		z.R = (f->n3) ? fabs(z.sqR - z.sqI + z.cR) : z.sqR - z.sqI + p->seed_jR;
	}
	return (get_color(win, z.iter));
}

int		batman_col(t_env *win, int x, int y)
{
	t_cnb	z;
	t_param	*p;
	t_flags	*f;

	p = win->param;
	f = win->flags;
	z.cR = (p->ratio * (x - p->center_x) / p->zoom + p->offset_x)
		   * ((f->n6) ? -1 : 1);
	z.cI = (y - p->center_y) / p->zoom + p->offset_y;
	if (!(z.iter = -1) || (f->Y && if_сardioid(win, z.cR, z.cI)))
		return ((f->W) ? 0xffffff : 0x0);
	z.R = (f->Q) ? z.cR : p->seed_jR;
	z.I = (f->E) ? z.cI : p->seed_jI;
	while (++z.iter < p->iter && !mandel_break(win, &z))
	{
		z.I = (pow2(z.R + z.I, 2) - z.sqR - z.sqI + z.cI) * ((f->n1) ? -1 : 1);
		z.I = (f->n2) ? fabs(z.I) : z.I;
		z.I *= (f->n7) ? -1 : 1;
		z.R = (f->n3) ? fabs(z.sqR - z.sqI + z.cR) : z.sqR * z.sqI + z.cR;
	}
	return (get_color(win, z.iter));
}

int		mandelbrot_cuboid(t_env *win, int x, int y)
{
	t_cnb	z;
	t_param	*p;
	t_flags	*f;

	p = win->param;
	f = win->flags;
	z.cR = (p->ratio * (x - p->center_x) / p->zoom + p->offset_x)
			* ((f->n6) ? -1 : 1);
	z.cI = (y - p->center_y) / p->zoom + p->offset_y;
	z.iter = -1;
	z.R = (f->Q) ? z.cR : p->seed_jR;
	z.I = (f->E) ? z.cI : p->seed_jI;
	while (++z.iter < p->iter && !mandel_break(win, &z))
	{
		z.oldI = (f->n2) ? fabs(z.I) : z.I;
		z.oldI *= (f->n7) ? -1 : 1;
		z.oldR = (f->n3) ? fabs(z.R) : z.R;
		z.I = 3 * z.sqR * z.oldI - pow2(z.oldI, 3) + z.cI;
		z.I *= ((f->n1) ? -1 : 1);
		z.R = pow2(z.oldR, 3) - 3 * z.oldR * z.sqI + z.cR;
	}
	return (get_color(win, z.iter));
}
