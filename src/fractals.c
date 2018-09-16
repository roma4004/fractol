/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 16:43:00 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/16 17:00:57 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "main.h"

int		get_mandelbrot(t_param *param, t_flags *flags, int x, int y)
{
	int		i;
	int		i_max;
	t_cnb	z;

	z.rc = param->ratio * (x - param->center_x)
			/ param->actial_zoom + param->offset_x;
	(flags->n6) ? z.rc *= -1 : 0;
	z.ic = ((y + param->i_mouse_move_seed - param->center_y)
			/ (param->actial_zoom) + param->offset_y);
	if (!flags->if_carioid && is_cardioid(param, flags, &z))
		return (flags->w ? 0xffffff : 0x0);
	z.r = flags->q ? z.rc : param->i_mouse_move_seed;
	z.i = flags->e ? z.ic : param->r_mouse_move_seed;
	i = -1;
	i_max = param->fr_depth;
	while (++i < i_max && !mandel_break(param, flags, &z))
	{
		z.i = (ft_pow(z.r + z.i, 2) - z.rsq - z.isq + z.ic);
		(flags->n1) ? z.i *= -1 : 0;
		(flags->n2) ? z.i = fabs(z.i) : 0;
		(flags->n7) ? z.i *= -1 : 0;
		z.r = z.rsq - z.isq + z.rc;
		(flags->n3) ? z.r = fabs(z.r) : 0;
	}
	return (get_color(param, flags, i));
}

int		get_julia(t_param *param, t_flags *flags, int x, int y)
{
	int		i;
	int		i_max;
	t_cnb	z;

	z.rc = param->ratio * (x - param->center_x)
			/ param->actial_zoom + param->offset_x;
	(flags->n6) ? z.rc *= -1 : 0;
	z.ic = (y - param->center_y) / param->actial_zoom + param->offset_y;
	z.r = flags->q ? ft_pow(z.rc, 2) : z.rc;
	z.i = flags->e ? ft_pow(z.ic, 2) : z.ic;
	i = -1;
	i_max = param->fr_depth;
	while (++i < i_max && !mandel_break(param, flags, &z))
	{
		z.i = (ft_pow(z.r + z.i, 2) - z.rsq - z.isq + param->i_mouse_move_seed);
		(flags->n1) ? z.i *= -1 : 0;
		(flags->n2) ? z.i = fabs(z.i) : 0;
		(flags->n7) ? z.i *= -1 : 0;
		z.r = z.rsq - z.isq + param->r_mouse_move_seed;
		(flags->n3) ? z.r = fabs(z.r) : 0;
	}
	return (get_color(param, flags, i));
}

int		get_batman(t_param *param, t_flags *flags, int x, int y)
{
	int		i;
	int		i_max;
	t_cnb	z;

	z.rc = param->ratio * (y - param->center_y)
			/ param->actial_zoom + param->offset_y;
	(flags->n6) ? z.rc *= -1 : 0;
	z.ic = (x - param->center_x) / param->actial_zoom + param->offset_x;
	if (!flags->if_carioid && is_cardioid(param, flags, &z))
		return (flags->w ? 0xffffff : 0x0);
	z.r = flags->q ? z.rc : param->r_mouse_move_seed;
	z.i = flags->e ? z.ic : param->i_mouse_move_seed;
	i = -1;
	i_max = param->fr_depth;
	while (++i < i_max && !mandel_break(param, flags, &z))
	{
		z.i = (ft_pow(z.r + z.i, 2) - z.rsq - z.isq + z.ic);
		(flags->n1) ? z.i *= -1 : 0;
		(flags->n2) ? z.i = fabs(z.i) : 0;
		(flags->n7) ? z.i *= -1 : 0;
		z.r = z.rsq * z.isq + z.rc;
		(flags->n3) ? z.r = fabs(z.r) : 0;
	}
	return (get_color(param, flags, i));
}

int		get_mandelbrot_cuboid(t_param *param, t_flags *flags, int x, int y)
{
	int		i;
	int		i_max;
	t_cnb	z;

	z.rc = param->ratio * (x - param->center_x)
			/ param->actial_zoom + param->offset_x;
	(flags->n6) ? z.rc *= -1 : 0;
	z.ic = (y - param->center_y) / param->actial_zoom + param->offset_y;
	z.r = flags->q ? z.rc : param->r_mouse_move_seed;
	z.i = flags->e ? z.ic : param->i_mouse_move_seed;
	i = -1;
	i_max = param->fr_depth;
	while (++i < i_max && !mandel_break(param, flags, &z))
	{
		z.iold = flags->n2 ? fabs(z.i) : z.i;
		(flags->n7) ? z.iold *= -1 : 0;
		z.rold = flags->n3 ? fabs(z.r) : z.r;
		z.i = 3 * z.rsq * z.iold - ft_pow(z.iold, 3) + z.ic;
		(flags->n1) ? z.i *= -1 : 0;
		z.r = ft_pow(z.rold, 3) - 3 * z.rold * z.isq + z.rc;
	}
	return (get_color(param, flags, i));
}
