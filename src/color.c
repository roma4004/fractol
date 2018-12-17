/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 14:33:57 by dromanic          #+#    #+#             */
/*   Updated: 2018/12/12 19:02:48 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		change_hue(int *color, int is_increase, int color_offset)
{
	int		mask;
	int		increment;

	mask = 0x000000FF << color_offset;
	increment = mask & 0x01010101;
	*color += (is_increase == 1) ? increment : -increment;
	return (*color);
}

static int		shift_apply(t_env *env, t_img *img, int offset, int chanel)
{
	int		y;
	int		x;

	if (offset)
	{
		y = -1;
		while (++y < (int)WIN_HEIGHT)
		{
			x = -1;
			while (++x < (int)WIN_WIDTH)
				change_hue(&img->data[y * (int)WIN_WIDTH + x], offset, chanel);
		}
		redraw_fract_or_img(env, env->param, 1);
		return (1);
	}
	return (0);
}

int				change_color(t_env *env, t_col_shift *col_shift, int key)
{
	int		offset;
	int		chanel;

	if (!env)
		return (0);
	offset = 0;
	if ((key == A || (key == Z)) && (chanel = ALPHA))
		col_shift->alpha += (key == A) ? (offset = 1)
										: (offset = -1);
	else if ((key == S || (key == X)) && (chanel = RED))
		col_shift->red += (key == S) ? (offset = 1)
										: (offset = -1);
	else if ((key == D || (key == C)) && (chanel = GREEN))
		col_shift->green += (key == D) ? (offset = 1)
										: (offset = -1);
	else if ((key == F || (key == V)) && !(chanel = BLUE))
		col_shift->blue += (key == F) ? (offset = 1)
										: (offset = -1);
	if (shift_apply(env, env->img, offset, chanel))
		return (1);
	return (0);
}

void			argb_shift(t_env *env, t_col_shift *col_shift)
{
	int		i;
	int		i_max;
	int		offset;

	i_max = (col_shift->alpha >= 0) ? col_shift->alpha : 0;
	i = (col_shift->alpha >= 0) ? -1 : col_shift->alpha - 1;
	offset = (col_shift->alpha >= 0) ? 1 : -1;
	while (++i < i_max)
		shift_apply(env, env->img, offset, ALPHA);
	i_max = (col_shift->red >= 0) ? col_shift->red : 0;
	i = (col_shift->red >= 0) ? -1 : col_shift->red - 1;
	offset = (col_shift->red >= 0) ? 1 : -1;
	while (++i < i_max)
		shift_apply(env, env->img, offset, RED);
	i_max = (col_shift->green >= 0) ? col_shift->green : 0;
	i = (col_shift->green >= 0) ? -1 : col_shift->green - 1;
	offset = (col_shift->green >= 0) ? 1 : -1;
	while (++i < i_max)
		shift_apply(env, env->img, offset, GREEN);
	i_max = (col_shift->blue >= 0) ? col_shift->blue : 0;
	i = (col_shift->blue >= 0) ? -1 : col_shift->blue - 1;
	offset = (col_shift->blue >= 0) ? 1 : -1;
	while (++i < i_max)
		shift_apply(env, env->img, offset, BLUE);
}

int				get_color(t_param *param, t_flags *flags, int i)
{
	int		color;
	double	step;
	t_color	col;

	if (!flags->alt_color)
	{
		color = (int)(param->col_step * i);
		return (color);
	}
	step = (double)i / (double)param->depth;
	col.a = 0;
	col.r = (int)(9 * (1 - step) * step * step * 255);
	col.g = (int)(15 * (1 - step) * (1 - step) * step * 255);
	col.b = (int)(8.5 * (1 - step) * (1 - step) * (1 - step) * 255);
	return ((col.a << 24) | ((col.r) << 16) | ((col.g) << 8) | (col.b));
}
