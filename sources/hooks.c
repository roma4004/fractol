/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 15:18:37 by dromanic          #+#    #+#             */
/*   Updated: 2019/04/21 21:56:45 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

unsigned int	map_offset(t_env *restrict env, int key,
						t_param param, t_db_pt *restrict offset)
{
	if (!env)
		return (0);
	if ((ARROW_LEFT == key && (_Bool)(offset->x += param.offset_step))
	|| (ARROW_UP == key && (_Bool)(offset->y += param.offset_step))
	|| (ARROW_DOWN == key && (_Bool)(offset->y -= param.offset_step))
	|| (ARROW_RIGHT == key && (_Bool)(offset->x -= param.offset_step)))
		return (redraw_fract_or_img(env, env->param, env->flags, 0));
	return (0);
}

unsigned int	specific_param(t_env *restrict env, t_param *restrict param,
								int key)
{
	if (!env || !param)
		return (0);
	if ((PAGE_UP == key && (_Bool)(param->ver += param->spec_step))
	|| (PAGE_DOWN == key && (_Bool)(param->ver -= param->spec_step))
	|| (HOME == key && (_Bool)(param->hor -= param->spec_step))
	|| (END == key && (_Bool)(param->hor += param->spec_step)))
		return (redraw_fract_or_img(env, env->param, env->flags, 0));
	return (0);
}

unsigned int			fr_depth(t_env *restrict env, t_param *restrict param,
								bool range, int key)
{
	int		offset;

	if (!env)
		return (0);
	offset = 0;
	if ((NUM_MUL == key && ++(param->depth_step))
	|| (NUM_DIV == key && --(param->depth_step)))
		return (redraw_fract_or_img(env, env->param, env->flags, 1));
	if ((((NUM_MINUS == key || I == key) && (offset = -param->depth_step))
		|| ((NUM_PLUS == key || O == key) && (offset = param->depth_step)))
	&& offset && (param->depth + offset > 0))
	{
		param->depth += offset;
		param->color_step = (range ? 0xFFFFFF : 0xFFFFFFFF) / param->depth;
		return (redraw_fract_or_img(env, env->param, env->flags, 0));
	}
	return (0);
}

unsigned int			zoom(t_env *restrict env, int key, t_db_pt pt)
{
	t_param		*param;

	param = &env->param;
	if ((PLUS == key
		&& param->display_zoom < 200
		&& (_Bool)(param->actial_zoom *= 1.5)
		&& (_Bool)(param->offset_step *= 0.5))
	|| (MINUS == key
		&& param->display_zoom > -10
		&& (_Bool)(param->actial_zoom *= 0.5)
		&& (_Bool)(param->offset_step *= 1.5)))
	{
		(PLUS == key) ? param->display_zoom++ : param->display_zoom--;
		param->offset.x += (pt.x - param->center.x) * param->center.x
							/ (param->actial_zoom * W_WIDTH);
		param->offset.y += (pt.y - param->center.y) * param->center.y
							/ (param->actial_zoom * W_HEIGHT);
		return (redraw_fract_or_img(env, env->param, env->flags, 0));
	}
	return (0);
}

unsigned int			toggles(t_env *restrict env, int key,
								t_param *restrict p, t_flags *restrict f)
{
	if (((NUM_1 == key || ONE == key) && ft_switch(&f->n1))
	|| ((NUM_2 == key || TWO == key) && ft_switch(&f->n2))
	|| ((NUM_3 == key || THREE == key) && ft_switch(&f->n3))
	|| ((NUM_4 == key || FOUR == key) && ft_switch(&f->n4))
	|| ((NUM_5 == key || FIVE == key) && ft_switch(&f->n5))
	|| ((NUM_6 == key || SIX == key) && ft_switch(&f->n6))
	|| ((NUM_7 == key || SEVEN == key) && ft_switch(&f->n7))
	|| ((NUM_8 == key || EIGHT == key) && ft_switch(&f->n8))
	|| ((NUM_9 == key || NINE == key) && ft_switch(&f->n9))
	|| ((NUM_0 == key || ZERO == key) && ft_switch(&f->n0))
	|| (Q == key && ft_switch(&f->q))
	|| (W == key && ft_switch(&f->w))
	|| (E == key && ft_switch(&f->e))
	|| (T == key && ft_switch(&f->range)
		&& (_Bool)(p->color_step =
					(f->range ? 0xFFFFFF : 0xFFFFFFFF) / p->depth))
	|| (Y == key && ft_switch(&f->carioid))
	|| (G == key && ft_switch(&f->alt_col)))
		return (redraw_fract_or_img(env, env->param, env->flags, 0));
	if ((U == key && (MAX_THREADS > p->threads ? ++(p->threads) : 0))
	|| (J == key && (1 < p->threads ? --(p->threads) : 0))
	|| (H == key && ft_switch(&f->hints))
	|| (N == key && ft_switch(&f->values))
	|| (M == key && ft_switch(&f->menu)))
		return (redraw_fract_or_img(env, env->param, env->flags, 1));
	return (0);
}
