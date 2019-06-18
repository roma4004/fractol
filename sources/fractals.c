/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 16:43:00 by dromanic          #+#    #+#             */
/*   Updated: 2019/05/11 18:45:02 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "main.h"

unsigned int	get_mandelbrot(t_env const *restrict env, t_param p,
								size_t x, size_t y)
{
	register const unsigned int		depth = p.depth;
	const t_flags					f = env->flags;
	register unsigned int			i;
	t_cnb							z;

	z.rc = (x - p.center.x) / p.actial_zoom + p.offset.x;
	(f.n6) ? z.rc *= -1 : 0;
	z.ic = (y + p.i_move_seed - p.center.y) / p.actial_zoom + p.offset.y;
	if (!f.carioid && is_cardioid(f, &z))
		return (f.w ? 0xffffff : 0x0);
	z.r = f.q ? z.rc : p.i_move_seed;
	z.i = f.e ? z.ic : p.r_move_seed;
	i = UINT32_MAX;
	while (depth > ++i && !mandel_break(p, f, &z))
	{
		z.i = (ft_pow(z.r + z.i, 2) - z.rsq - z.isq + z.ic);
		(f.n1) ? z.i *= -1 : 0;
		(f.n2) ? z.i = fabs(z.i) : 0;
		(f.n7) ? z.i *= -1 : 0;
		z.r = z.rsq - z.isq + z.rc;
		(f.n3) ? z.r = fabs(z.r) : 0;
	}
	return (get_color(f.alt_col, p.color_step, depth, i));
}

unsigned int	get_julia(t_env const *restrict env, t_param p,
							size_t x, size_t y)
{
	register const unsigned int		depth = p.depth;
	const t_flags					f = env->flags;
	register unsigned int			i;
	t_cnb							z;

	z.rc = (x - p.center.x) / p.actial_zoom + p.offset.x;
	(f.n6) ? z.rc *= -1 : 0;
	z.ic = (y - p.center.y) / p.actial_zoom + p.offset.y;
	z.r = f.q ? ft_pow(z.rc, 2) : z.rc;
	z.i = f.e ? ft_pow(z.ic, 2) : z.ic;
	i = UINT32_MAX;
	while (depth > ++i && !mandel_break(p, f, &z))
	{
		z.i = (ft_pow(z.r + z.i, 2) - z.rsq - z.isq + p.i_move_seed);
		(f.n1) ? z.i *= -1 : 0;
		(f.n2) ? z.i = fabs(z.i) : 0;
		(f.n7) ? z.i *= -1 : 0;
		z.r = z.rsq - z.isq + p.r_move_seed;
		(f.n3) ? z.r = fabs(z.r) : 0;
	}
	return (get_color(f.alt_col, p.color_step, depth, i));
}

unsigned int	get_batman(t_env const *restrict env, t_param p,
							size_t x, size_t y)
{
	register const unsigned int		depth = p.depth;
	const t_flags					f = env->flags;
	register unsigned int			i;
	t_cnb							z;

	z.rc = (y - p.center.y) / p.actial_zoom + p.offset.y;
	(f.n6) ? z.rc *= -1 : 0;
	z.ic = (x - p.center.x) / p.actial_zoom + p.offset.x;
	if (!f.carioid && is_cardioid(f, &z))
		return (f.w ? 0xffffff : 0x0);
	z.r = f.q ? z.rc : p.r_move_seed;
	z.i = f.e ? z.ic : p.i_move_seed;
	i = UINT32_MAX;
	while (depth > ++i && !mandel_break(p, f, &z))
	{
		z.i = (ft_pow(z.r + z.i, 2) - z.rsq - z.isq + z.ic);
		(f.n1) ? z.i *= -1 : 0;
		(f.n2) ? z.i = fabs(z.i) : 0;
		(f.n7) ? z.i *= -1 : 0;
		z.r = z.rsq * z.isq + z.rc;
		(f.n3) ? z.r = fabs(z.r) : 0;
	}
	return (get_color(f.alt_col, p.color_step, depth, i));
}

unsigned int	get_mandelbrot_cuboid(t_env const *restrict env, t_param p,
										size_t x, size_t y)
{
	register const unsigned int		depth = p.depth;
	const t_flags					f = env->flags;
	register unsigned int			i;
	t_cnb							z;

	z.rc = (x - p.center.x) / p.actial_zoom + p.offset.x;
	(f.n6) ? z.rc *= -1 : 0;
	z.ic = (y - p.center.y) / p.actial_zoom + p.offset.y;
	z.r = f.q ? z.rc : p.r_move_seed;
	z.i = f.e ? z.ic : p.i_move_seed;
	i = UINT32_MAX;
	while (depth > ++i && !mandel_break(p, f, &z))
	{
		z.iold = f.n2 ? fabs(z.i) : z.i;
		(f.n7) ? z.iold *= -1 : 0;
		z.rold = f.n3 ? fabs(z.r) : z.r;
		z.i = 3 * z.rsq * z.iold - ft_pow(z.iold, 3) + z.ic;
		(f.n1) ? z.i *= -1 : 0;
		z.r = ft_pow(z.rold, 3) - 3 * z.rold * z.isq + z.rc;
	}
	return (get_color(f.alt_col, p.color_step, depth, i));
}
