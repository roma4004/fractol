/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 14:33:57 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/11 17:59:23 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		change_hue(int color, int offset, int mask_offset)
{
	int mask;
	int increment;

	mask = 0x000000FF << mask_offset;
	increment = mask & 0x01010101;
	if (offset == 1)
		color += increment;
	else
		color -= increment;
	return (color);
}

static int		shift_apply(t_env *env, int offset, int chanel)
{
	int		y;
	int		x;

	if (offset && (y = -1))
	{
		while (++y < WIN_HEIGHT && (x = -1))
			while (++x < WIN_WIDTH)
				px_to_img(env->img, x, y,
				change_hue(env->img->data[y * WIN_WIDTH + x], offset, chanel));
		redraw_fract(env, 1);
		return (1);
	}
	return (0);
}

int				change_color(t_env *env, int key)
{
	int		offset;
	int		chanel;
	t_param	*param;

	if (!env)
		return (0);
	offset = 0;
	param = env->param;
	if ((key == A || (key == Z)) && (chanel = ALPHA))
		param->alpha_shift_iter += (key == A) ? (offset = 1)
											: (offset = -1);
	else if ((key == S || (key == X)) && (chanel = RED))
		param->red_shift_iter += (key == S) ? (offset = 1)
											: (offset = -1);
	else if ((key == D || (key == C)) && (chanel = GREEN))
		param->green_shift_iter += (key == D) ? (offset = 1)
											: (offset = -1);
	else if ((key == F || (key == V)) && !(chanel = BLUE))
		param->blue_shift_iter += (key == F) ? (offset = 1)
											: (offset = -1);
	if (shift_apply(env, offset, chanel))
		return (1);
	return (0);
}

void			argb_shift(t_env *env, t_param *param)
{
	double	i;
	double	i_max;
	double	offset;

	i_max = (param->alpha_shift_iter >= 0) ? param->alpha_shift_iter : 0;
	i = (param->alpha_shift_iter >= 0) ? -1 : param->alpha_shift_iter - 1;
	offset = (param->alpha_shift_iter >= 0) ? 1 : -1;
	while (++i < i_max)
		shift_apply(env, offset, ALPHA);
	i_max = (param->red_shift_iter >= 0) ? param->red_shift_iter : 0;
	i = (param->red_shift_iter >= 0) ? -1 : param->red_shift_iter - 1;
	offset = (param->red_shift_iter >= 0) ? 1 : -1;
	while (++i < i_max)
		shift_apply(env, offset, RED);
	i_max = (param->green_shift_iter >= 0) ? param->green_shift_iter : 0;
	i = (param->green_shift_iter >= 0) ? -1 : param->green_shift_iter - 1;
	offset = (param->green_shift_iter >= 0) ? 1 : -1;
	while (++i < i_max)
		shift_apply(env, offset, GREEN);
	i_max = (param->blue_shift_iter >= 0) ? param->blue_shift_iter : 0;
	i = (param->blue_shift_iter >= 0) ? -1 : param->blue_shift_iter - 1;
	offset = (param->blue_shift_iter >= 0) ? 1 : -1;
	while (++i < i_max)
		shift_apply(env, offset, BLUE);
}

int				get_color(t_env *env, int i)
{
	int		color;
	double	step;
	t_img	*img;
	t_col	*col;

	if (!env->flags->alt_color)
	{
		color = (int)(env->param->col_step * i);
		return (color);
	}
	img = env->img;
	step = (double)i / (double)env->param->i_max;
	img->col.a = 0;
	img->col.r = (int)(9 * (1 - step) * step * step * 255);
	img->col.g = (int)(15 * (1 - step) * (1 - step) * step * 255);
	img->col.b = (int)(8.5 * (1 - step) * (1 - step) * (1 - step) * 255);
	col = &env->img->col;
	return ((col->a << 24) | ((col->r) << 16) | ((col->g) << 8) | (col->b));
}
