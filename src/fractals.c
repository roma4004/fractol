/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 16:43:00 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/09 15:46:49 by dromanic         ###   ########.fr       */
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
	z.cR = (p->ratio * (x - p->center_x) / p->zoom + p->offset_x)
		* ((f->n6) ? -1 : 1);
	z.cI = ((y + p->seed_jI - p->center_y) / (p->zoom) + p->offset_y);
	if (!(z.iter = -1) || (f->Y && if_сardioid(env, z.cR, z.cI)))
		return ((f->W) ? 0xffffff : 0x0);
	z.R = (f->Q) ? z.cR : p->seed_jI;
	z.I = (f->E) ? z.cI : p->seed_jR;
	while (++z.iter < p->iter && !mandel_break(env, &z))
	{
		z.I = (pow2(z.R + z.I, 2) - z.sqR - z.sqI + z.cI) * ((f->n1) ? -1 : 1);
		z.I = (f->n2) ? fabs(z.I) : z.I;
		z.I *= (f->n7) ? -1 : 1;
		z.R = (f->n3) ? fabs(z.sqR - z.sqI + z.cR) : z.sqR - z.sqI + z.cR;
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
	z.cR = (p->ratio * (x - p->center_x) / p->zoom + p->offset_x)
		* ((f->n6) ? -1 : 1);
	z.cI = (y - p->center_y) / p->zoom + p->offset_y;
	if (!(z.iter = -1) || (f->Y && if_сardioid(env, z.cR, z.cI)))
		return ((f->W) ? 0xffffff : 0x0);
	z.R = (f->Q) ? 0 : z.cR;
	z.I = (f->E) ? 0 : z.cI;
	while (++z.iter < p->iter && !mandel_break(env, &z))
	{
		z.I = (pow2(z.R + z.I, 2) - z.sqR - z.sqI + p->seed_jI)
			* ((f->n1) ? -1 : 1);
		z.I = (f->n2) ? fabs(z.I) : z.I;
		z.I *= (f->n7) ? -1 : 1;
		z.R = (f->n3) ? fabs(z.sqR - z.sqI + z.cR) : z.sqR - z.sqI + p->seed_jR;
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
	z.cR = (p->ratio * (x - p->center_x) / p->zoom + p->offset_x)
		* ((f->n6) ? -1 : 1);
	z.cI = (y - p->center_y) / p->zoom + p->offset_y;
	if (!(z.iter = -1) || (f->Y && if_сardioid(env, z.cR, z.cI)))
		return ((f->W) ? 0xffffff : 0x0);
	z.R = (f->Q) ? z.cR : p->seed_jR;
	z.I = (f->E) ? z.cI : p->seed_jI;
	while (++z.iter < p->iter && !mandel_break(env, &z))
	{
		z.I = (pow2(z.R + z.I, 2) - z.sqR - z.sqI + z.cI) * ((f->n1) ? -1 : 1);
		z.I = (f->n2) ? fabs(z.I) : z.I;
		z.I *= (f->n7) ? -1 : 1;
		z.R = (f->n3) ? fabs(z.sqR - z.sqI + z.cR) : z.sqR * z.sqI + z.cR;
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
	z.cR = (p->ratio * (x - p->center_x) / p->zoom + p->offset_x)
			* ((f->n6) ? -1 : 1);
	z.cI = (y - p->center_y) / p->zoom + p->offset_y;
	z.iter = -1;
	z.R = (f->Q) ? z.cR : p->seed_jR;
	z.I = (f->E) ? z.cI : p->seed_jI;
	while (++z.iter < p->iter && !mandel_break(env, &z))
	{
		z.oldI = (f->n2) ? fabs(z.I) : z.I;
		z.oldI *= (f->n7) ? -1 : 1;
		z.oldR = (f->n3) ? fabs(z.R) : z.R;
		z.I = 3 * z.sqR * z.oldI - pow2(z.oldI, 3) + z.cI;
		z.I *= ((f->n1) ? -1 : 1);
		z.R = pow2(z.oldR, 3) - 3 * z.oldR * z.sqI + z.cR;
	}
	return (get_color(env, z.iter));
}
