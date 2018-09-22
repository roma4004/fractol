/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 15:18:37 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/16 17:16:55 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int			map_offset(t_env *env, int key, t_param *param)
{
	if (!env || !param)
		return (0);
	if ((key == ARROW_LEFT && (param->offset_x += param->offset_step))
	|| (key == ARROW_UP && (param->offset_y += param->offset_step))
	|| (key == ARROW_DOWN && (param->offset_y -= param->offset_step))
	|| (key == ARROW_RIGHT && (param->offset_x -= param->offset_step)))
	{
		redraw_fract_or_img(env, 0);
		return (1);
	}
	return (0);
}

int			specific_param(t_env *env, t_param *param, int key)
{
	if ((key == PAGE_UP && (param->spec2 += param->spec_step))
	|| (key == PAGE_DOWN && (param->spec2 -= param->spec_step))
	|| (key == HOME && (param->spec1 -= param->spec_step))
	|| (key == END && (param->spec1 += param->spec_step)))
	{
		redraw_fract_or_img(env, 0);
		return (1);
	}
	return (0);
}

int			fr_depth(t_env *env, t_param *param, t_flags *flags, int key)
{
	int		offset;

	offset = 0;
	if ((key == NUM_MUL && param->fr_depth_step++)
	|| (key == NUM_DIV && param->fr_depth_step--))
	{
		redraw_fract_or_img(env, 1);
		return (1);
	}
	if (((key == NUM_MINUS || key == NINE || key == NUM_9)
		&& (offset = -param->fr_depth_step))
	|| ((key == NUM_PLUS || key == ZERO || key == NUM_0)
		&& (offset = param->fr_depth_step)))
		if (offset && (param->fr_depth + offset > 0))
		{
			param->fr_depth += offset;
			param->col_step =
				(flags->col_range ? 0xFFFFFF : 0xFFFFFFFF) / param->fr_depth;
			redraw_fract_or_img(env, 0);
			return (1);
		}
	return (0);
}

int			zoom(t_env *env, int key, float x, float y)
{
	t_param	*param;

	param = env->param;
	if ((key == PLUS
		&& (param->actial_zoom *= 1.5)
		&& (param->offset_step /= 1.5))
	|| (key == MINUS
		&& (param->display_zoom > -10)
		&& (param->actial_zoom /= 1.5)
		&& (param->offset_step *= 1.5)))
	{
		(key == PLUS) ? param->display_zoom++ : param->display_zoom--;
		param->offset_x += (x - param->center_x) * param->center_x
							/ (param->actial_zoom * WIN_WIDTH);
		param->offset_y += (y - param->center_y) * param->center_y
							/ (param->actial_zoom * WIN_HEIGHT);
		redraw_fract_or_img(env, 0);
		return (1);
	}
	return (0);
}

int			toggles(t_env *env, int key, t_param *p, t_flags *f)
{
	if (((key == NUM_1 || key == ONE) && (f->n1 = ~f->n1) <= 1)
	|| ((key == NUM_2 || key == TWO) && (f->n2 = ~f->n2) <= 1)
	|| ((key == NUM_3 || key == THREE) && (f->n3 = ~f->n3) <= 1)
	|| ((key == NUM_4 || key == FOUR) && (f->n4 = ~f->n4) <= 1)
	|| ((key == NUM_5 || key == FIVE) && (f->n5 = ~f->n5) <= 1)
	|| ((key == NUM_6 || key == SIX) && (f->n6 = ~f->n6) <= 1)
	|| ((key == NUM_7 || key == SEVEN) && (f->n7 = ~f->n7) <= 1)
	|| ((key == NUM_8 || key == EIGHT) && (f->n8 = ~f->n8) <= 1)
	|| (key == Q && (f->q = ~f->q) <= 1)
	|| (key == W && (f->w = ~f->w) <= 1)
	|| (key == E && (f->e = ~f->e) <= 1)
	|| (key == U && (p->threads < MAX_THREADS ? p->threads++ : 0))
	|| (key == J && (p->threads > 1 ? p->threads-- : 0))
	|| (key == T && (f->col_range = ~f->col_range) <= 1
		&& (p->col_step = (f->col_range ? 0xFFFFFF : 0xFFFFFFFF) / p->fr_depth))
	|| (key == Y && (f->if_carioid = ~f->if_carioid) <= 1)
	|| (key == G && (f->alt_color = ~f->alt_color) <= 1)
	|| (key == H && (f->hints_off = ~f->hints_off) <= 1)
	|| (key == N && (f->values_off = ~f->values_off) <= 1)
	|| (key == M && (f->menu_off = ~f->menu_off) <= 1))
	{
		redraw_fract_or_img(env, 0);
		return (1);
	}
	return (0);
}
