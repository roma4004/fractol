/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 15:18:37 by dromanic          #+#    #+#             */
/*   Updated: 2018/12/25 19:17:24 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int			map_offset(t_env *env, int key, t_param *param)
{
	if (!env || !param)
		return (0);
	if ((key == ARROW_LEFT && (param->offset.x += param->offset_step))
	|| (key == ARROW_UP && (param->offset.y += param->offset_step))
	|| (key == ARROW_DOWN && (param->offset.y -= param->offset_step))
	|| (key == ARROW_RIGHT && (param->offset.x -= param->offset_step)))
	{
		redraw_fract_or_img(env, env->param, 0);
		return (1);
	}
	return (0);
}

int			specific_param(t_env *env, t_param *param, int key)
{
	if (!env || !param)
		return (0);
	if ((key == PAGE_UP && (param->spec2 += param->spec_step))
	|| (key == PAGE_DOWN && (param->spec2 -= param->spec_step))
	|| (key == HOME && (param->spec1 -= param->spec_step))
	|| (key == END && (param->spec1 += param->spec_step)))
	{
		redraw_fract_or_img(env, env->param, 0);
		return (1);
	}
	return (0);
}

int			fr_depth(t_env *env, t_param *param, t_flags *flags, int key)
{
	int		offset;

	if (!env || !param)
		return (0);
	offset = 0;
	if ((key == NUM_MUL && param->depth_step++)
	|| (key == NUM_DIV && param->depth_step--))
	{
		redraw_fract_or_img(env, env->param, 1);
		return (1);
	}
	if (((key == NUM_MINUS || key == NINE || key == NUM_9)
			&& (offset = -param->depth_step))
	|| ((key == NUM_PLUS || key == ZERO || key == NUM_0)
			&& (offset = param->depth_step)))
		if (offset && (param->depth + offset > 0))
		{
			param->depth += offset;
			param->col_step =
				(flags->range ? 0xFFFFFF : 0xFFFFFFFF) / param->depth;
			redraw_fract_or_img(env, env->param, 0);
			return (1);
		}
	return (0);
}

int			zoom(t_env *env, int key, float x, float y)
{
	t_param	*param;

	param = env->param;
	if ((key == PLUS//	&& (param->display_zoom > 200)
		&& (param->actial_zoom *= 1.5)
		&& (param->offset_step /= 1.5))
	|| (key == MINUS
		&& (param->display_zoom > -10)
		&& (param->actial_zoom /= 1.5)
		&& (param->offset_step *= 1.5)))
	{
		(key == PLUS) ? param->display_zoom++ : param->display_zoom--;
		param->offset.x += (x - param->center.x) * param->center.x
							/ (param->actial_zoom * WIN_WIDTH);
		param->offset.y += (y - param->center.y) * param->center.y
							/ (param->actial_zoom * WIN_HEIGHT);
		redraw_fract_or_img(env, env->param, 0);
		return (1);
	}
	return (0);
}

int			toggles(t_env *env, int k, t_param *p, t_flags *f)
{
	if (((k == NUM_1 || k == ONE) && ft_switch(&f->n1))
	|| ((k == NUM_2 || k == TWO) && ft_switch(&f->n2))
	|| ((k == NUM_3 || k == THREE) && ft_switch(&f->n3))
	|| ((k == NUM_4 || k == FOUR) && ft_switch(&f->n4))
	|| ((k == NUM_5 || k == FIVE) && ft_switch(&f->n5))
	|| ((k == NUM_6 || k == SIX) && ft_switch(&f->n6))
	|| ((k == NUM_7 || k == SEVEN) && ft_switch(&f->n7))
	|| ((k == NUM_8 || k == EIGHT) && ft_switch(&f->n8))
	|| (k == Q && ft_switch(&f->q)) || (k == W && ft_switch(&f->w))
	|| (k == E && ft_switch(&f->e)) || (k == T && ft_switch(&f->range)
		&& (p->col_step = (f->range ? 0xFFFFFF : 0xFFFFFFFF) / p->depth))
	|| (k == Y && ft_switch(&f->carioid)) || (k == G && ft_switch(&f->alt_color)))
	{
		redraw_fract_or_img(env, env->param, 0);
		return (1);
	}
	if ((k == U && (p->threads < MAX_THREADS ? p->threads++ : 0))
	|| (k == J && (p->threads > 1 ? p->threads-- : 0))
	|| (k == H && ft_switch(&f->hints)) || (k == N && ft_switch(&f->values))
	|| (k == M && ft_switch(&f->menu)))
	{
		redraw_fract_or_img(env, env->param, 1);
		return (1);
	}
	return (0);
}
