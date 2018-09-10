/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 16:43:00 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/10 16:51:11 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <math.h>

int		mandelbrot_col(t_env *env, int x, int y)
{
	t_cnb	z;
	t_param	*p;
	t_flags	*f;

	p = env->param;
	f = env->flags;
	z.rc = (p->ratio * (x - p->center_x) / p->zoom + p->offset_x)
		* ((f->n6) ? -1 : 1);
	z.ic = ((y + p->ij_seed - p->center_y) / (p->zoom) + p->offset_y);
	if (!(z.iter = -1) || (!f->if_carioid && if_сardioid(env, z.rc, z.ic)))
		return ((f->w) ? 0xffffff : 0x0);
	z.r = (f->q) ? z.rc : p->ij_seed;
	z.i = (f->e) ? z.ic : p->rj_seed;
	while (++z.iter < p->iter_max && !mandel_break(env, &z))
	{
		z.i = (pow2(z.r + z.i, 2) - z.rsq - z.isq + z.ic) * ((f->n1) ? -1 : 1);
		z.i = (f->n2) ? fabs(z.i) : z.i;
		z.i *= (f->n7) ? -1 : 1;
		z.r = (f->n3) ? fabs(z.rsq - z.isq + z.rc) : z.rsq - z.isq + z.rc;
	}
	return (get_color(env, z.iter));
}

int		julia_col(t_env *env, int x, int y)
{
	t_cnb	z;
	t_param	*p;
	t_flags	*f;

	p = env->param;
	f = env->flags;
	z.rc = (p->ratio * (x - p->center_x) / p->zoom + p->offset_x)
		* ((f->n6) ? -1 : 1);
	z.ic = (y - p->center_y) / p->zoom + p->offset_y;
	if (!(z.iter = -1) || (!f->if_carioid && if_сardioid(env, z.rc, z.ic)))
		return ((f->w) ? 0xffffff : 0x0);
	z.r = (f->q) ? 0 : z.rc;
	z.i = (f->e) ? 0 : z.ic;
	while (++z.iter < p->iter_max && !mandel_break(env, &z))
	{
		z.i = (pow2(z.r + z.i, 2) - z.rsq - z.isq + p->ij_seed)
			* ((f->n1) ? -1 : 1);
		z.i = (f->n2) ? fabs(z.i) : z.i;
		z.i *= (f->n7) ? -1 : 1;
		z.r = (f->n3) ? fabs(z.rsq - z.isq + z.rc) : z.rsq - z.isq + p->rj_seed;
	}
	return (get_color(env, z.iter));
}

int		batman_col(t_env *env, int x, int y)
{
	t_cnb	z;
	t_param	*p;
	t_flags	*f;

	p = env->param;
	f = env->flags;
	z.rc = (p->ratio * (x - p->center_x) / p->zoom + p->offset_x)
		* ((f->n6) ? -1 : 1);
	z.ic = (y - p->center_y) / p->zoom + p->offset_y;
	if (!(z.iter = -1) || (!f->if_carioid && if_сardioid(env, z.rc, z.ic)))
		return ((f->w) ? 0xffffff : 0x0);
	z.r = (f->q) ? z.rc : p->rj_seed;
	z.i = (f->e) ? z.ic : p->ij_seed;
	while (++z.iter < p->iter_max && !mandel_break(env, &z))
	{
		z.i = (pow2(z.r + z.i, 2) - z.rsq - z.isq + z.ic) * ((f->n1) ? -1 : 1);
		z.i = (f->n2) ? fabs(z.i) : z.i;
		z.i *= (f->n7) ? -1 : 1;
		z.r = (f->n3) ? fabs(z.rsq - z.isq + z.rc) : z.rsq * z.isq + z.rc;
	}
	return (get_color(env, z.iter));
}

int		mandelbrot_cuboid(t_env *env, int x, int y)
{
	t_cnb	z;
	t_param	*p;
	t_flags	*f;

	p = env->param;
	f = env->flags;
	z.rc = (p->ratio * (x - p->center_x) / p->zoom + p->offset_x)
			* ((f->n6) ? -1 : 1);
	z.ic = (y - p->center_y) / p->zoom + p->offset_y;
	z.iter = -1;
	z.r = (f->q) ? z.rc : p->rj_seed;
	z.i = (f->e) ? z.ic : p->ij_seed;
	while (++z.iter < p->iter_max && !mandel_break(env, &z))
	{
		z.iold = (f->n2) ? fabs(z.i) : z.i;
		z.iold *= (f->n7) ? -1 : 1;
		z.rold = (f->n3) ? fabs(z.r) : z.r;
		z.i = 3 * z.rsq * z.iold - pow2(z.iold, 3) + z.ic;
		z.i *= ((f->n1) ? -1 : 1);
		z.r = pow2(z.rold, 3) - 3 * z.rold * z.isq + z.rc;
	}
	return (get_color(env, z.iter));
}
