/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 14:33:57 by dromanic          #+#    #+#             */
/*   Updated: 2019/03/22 19:16:48 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static unsigned int		change_hue(unsigned *color, int is_increase,
									unsigned int color_bit_shift)
{
	unsigned int	mask;
	unsigned int	increment;

	mask = 0x000000FFU << color_bit_shift;
	increment = mask & 0x01010101U;
	*color += (is_increase == 1) ? increment : -increment;
	return (*color);
}

static unsigned int		shift_apply(t_env *env, int offset, unsigned int chanel)
{
	int		y;
	int		x;

	y = -1;
	while (++y < W_HEIGHT)
	{
		x = -1;
		while (++x < W_WIDTH)
			change_hue(&env->surface[y * W_WIDTH + x], offset, chanel);
	}
	redraw_fract_or_img(env, env->param, 1);
	return (1);
}

unsigned int			change_color(t_env *env, t_col_shift *col_shift,
										int key)
{
	int				offset;
	unsigned int	chanel;

	if (!env)
		return (0);
	offset = 0;
	if ((key == A || (key == Z)) && (chanel = ALPHA))
		col_shift->alpha +=
			(offset = (key == A) ? 1 : -1);
	else if ((key == S || (key == X)) && (chanel = RED))
		col_shift->red +=
			(offset = (key == S) ? 1 : -1);
	else if ((key == D || (key == C)) && (chanel = GREEN))
		col_shift->green +=
			(offset = (key == D) ? 1 : -1);
	else if ((key == F || (key == V)) && !(chanel = BLUE))
		col_shift->blue +=
			(offset = (key == F) ? 1 : -1);
	if (shift_apply(env, offset, chanel))
		return (1);
	return (0);
}

void					argb_shift(t_env *env, t_col_shift *col_shift)
{
	int		i;
	int		i_max;
	int		offset;

	i_max = (col_shift->alpha >= 0) ? col_shift->alpha : 0;
	i = (col_shift->alpha >= 0) ? -1 : col_shift->alpha - 1;
	offset = (col_shift->alpha >= 0) ? 1 : -1;
	while (++i < i_max)
		shift_apply(env, offset, ALPHA);
	i_max = (col_shift->red >= 0) ? col_shift->red : 0;
	i = (col_shift->red >= 0) ? -1 : col_shift->red - 1;
	offset = (col_shift->red >= 0) ? 1 : -1;
	while (++i < i_max)
		shift_apply(env, offset, RED);
	i_max = (col_shift->green >= 0) ? col_shift->green : 0;
	i = (col_shift->green >= 0) ? -1 : col_shift->green - 1;
	offset = (col_shift->green >= 0) ? 1 : -1;
	while (++i < i_max)
		shift_apply(env, offset, GREEN);
	i_max = (col_shift->blue >= 0) ? col_shift->blue : 0;
	i = (col_shift->blue >= 0) ? -1 : col_shift->blue - 1;
	offset = (col_shift->blue >= 0) ? 1 : -1;
	while (++i < i_max)
		shift_apply(env, offset, BLUE);
}

unsigned int			get_color(t_param *param, t_flags *flags,
									unsigned int i)
{
	unsigned int	color;
	double			step;
	t_color			col;

	if (!flags->alt_col)
	{
		color = (unsigned int)(param->col_step * i);
		return (color);
	}
	step = (double)i / (double)param->depth;
	col.a = 0;
	col.r = (unsigned int)(9 * (1 - step) * step * step * 255);
	col.g = (unsigned int)(15 * (1 - step) * (1 - step) * step * 255);
	col.b = (unsigned int)(8.5 * (1 - step) * (1 - step) * (1 - step) * 255);
	return ((col.a << 24U) | ((col.r) << 16U) | ((col.g) << 8U) | (col.b));
}
