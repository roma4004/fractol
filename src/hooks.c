/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 15:18:37 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/10 17:34:01 by dromanic         ###   ########.fr       */
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
		redraw_fract(env, 0);
		return (1);
	}
	return (0);
}

int			specific_param(t_env *env, int key, t_param *param)
{
	if ((key == PAGE_UP && (param->spec2 += param->spec_step))
	|| (key == PAGE_DOWN && (param->spec2 -= param->spec_step))
	|| (key == HOME && (param->spec1 -= param->spec_step))
	|| (key == END && (param->spec1 += param->spec_step)))
	{
		redraw_fract(env, 0);
		return (1);
	}
	return (0);
}

int			iterate_change(t_env *env, int key)
{
	int		iter_offset;
	t_param	*p;
	t_flags	*f;

	p = env->param;
	f = env->flags;
	iter_offset = 0;
	if ((key == NUM_MUL && (p->iter_step += 1))
	|| (key == NUM_DIV && (p->iter_step -= 1)))
	{
		redraw_fract(env, 1);
		return (1);
	}
	if (((key == NUM_MINUS || key == NINE) && (iter_offset = -p->iter_step))
	|| ((key == NUM_PLUS || key == ZERO) && (iter_offset = p->iter_step)))
		if (iter_offset && (p->iter_max + iter_offset > 0))
		{
			p->iter_max += iter_offset;
			p->color_step = ((f->col_range) ? 0xFFFFFF : 0xFFFFFFFF)
						/ p->iter_max;
			redraw_fract(env, 0);
			return (1);
		}
	return (0);
}

int			zoom(t_env *env, int key, float x, float y)
{
	t_param	*par;

	par = env->param;
	if ((key == PLUS
		&& (par->zoom *= 1.5)
		&& (par->offset_step /= 1.5))
	|| (key == MINUS
		&& (par->zoom /= 1.5)
		&& (par->offset_step *= 1.5)))
	{
		par->offset_x +=
			(x - par->center_x) * par->center_x / (par->zoom * WIN_WIDTH);
		par->offset_y +=
			(y - par->center_y) * par->center_y / (par->zoom * WIN_HEIGHT);
		redraw_fract(env, 0);
		return (1);
	}
	return (0);
}

int			toggles(t_env *env, int key, t_param *p, t_flags *f)
{
	if (((key == NUM_1 || key == ONE) && toggle_flag(&f->n1))
		|| ((key == NUM_2 || key == TWO) && toggle_flag(&f->n2))
		|| ((key == NUM_3 || key == THREE) && toggle_flag(&f->n3))
		|| ((key == NUM_4 || key == FOUR) && toggle_flag(&f->n4))
		|| ((key == NUM_5 || key == FIVE) && toggle_flag(&f->n5))
		|| ((key == NUM_6 || key == SIX) && toggle_flag(&f->n6))
		|| ((key == NUM_7 || key == SEVEN) && toggle_flag(&f->n7))
		|| ((key == NUM_8 || key == EIGHT) && toggle_flag(&f->n8))
		|| (key == Q && toggle_flag(&f->q))
		|| (key == W && toggle_flag(&f->w))
		|| (key == E && toggle_flag(&f->e))
		|| (key == T && toggle_flag(&f->col_range)
			&& (p->color_step = ((f->col_range) ? 0xFFFFFF : 0xFFFFFFFF)
							/ p->iter_max))
		|| (key == Y && toggle_flag(&f->if_carioid))
		|| (key == G && toggle_flag(&f->alt_color))
		|| (key == H && toggle_flag(&f->hints_on))
		|| (key == N && toggle_flag(&f->values_on))
		|| (key == M && toggle_flag(&f->menu_on)))
	{
		redraw_fract(env, 0);
		return (1);
	}
	return (0);
}
