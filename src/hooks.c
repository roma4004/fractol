/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 15:18:37 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/11 21:27:11 by dromanic         ###   ########.fr       */
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
		if (iter_offset && (p->i_max + iter_offset > 0))
		{
			p->i_max += iter_offset;
			p->col_step = ((f->col_range) ? 0xFFFFFF : 0xFFFFFFFF)
						/ p->i_max;
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
	|| (key == T && (f->col_range = ~f->col_range) <= 1
		&& (p->col_step = ((f->col_range) ? 0xFFFFFF : 0xFFFFFFFF) / p->i_max))
	|| (key == Y && (f->if_carioid = ~f->if_carioid) <= 1)
	|| (key == G && (f->alt_color = ~f->alt_color) <= 1)
	|| (key == H && (f->hints_on = ~f->hints_on) <= 1)
	|| (key == N && (f->values_on = ~f->values_on) <= 1)
	|| (key == M && (f->menu_on = ~f->menu_on) <= 1))
	{
		redraw_fract(env, 0);
		return (1);
	}
	return (0);
}
