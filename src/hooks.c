/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 15:18:37 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/09 20:03:58 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int			map_offset(t_env *env, int key)
{
	double	offset_x;
	double	offset_y;

	if (!env)
		return (0);
	offset_x = 0;
	offset_y = 0;
	if ((key == ARROW_LEFT && (offset_x = env->param->offset_step))
	|| (key == ARROW_UP && (offset_y = env->param->offset_step))
	|| (key == ARROW_DOWN && (offset_y = -env->param->offset_step))
	|| (key == ARROW_RIGHT && (offset_x = -env->param->offset_step)))
	{
		env->param->offset_x += offset_x;
		env->param->offset_y += offset_y;
		redraw_fract(env);
		return (1);
	}
	return (0);
}

int			specific_param(t_env *env, int key)
{
	int		need_redraw;
	t_param	*param;

	param = env->param;
	need_redraw = 0;
	if ((key == PAGE_UP || key == PAGE_DOWN) && (need_redraw = 1))
		param->spec2 += (key == PAGE_UP) ? param->spec_step : -param->spec_step;
	else if ((key == HOME || key == END) && (need_redraw = 1))
		param->spec1 += (key == HOME) ? -param->spec_step : param->spec_step;
	if (need_redraw)
	{
		redraw_fract(env);
		return (1);
	}
	return (0);
}

int			iterate_change(t_env *env, int key)
{
	int		iter_offset;
	t_param	*par;
	t_flags	*fl;

	par = env->param;
	fl = env->flags;
	iter_offset = 0;
	if ((key == NUM_DIV && (par->iter_step += 1))
	|| (key == NUM_MUL && (par->iter_step -= 1)))
		return (1);
	if (((key == NUM_MINUS || key == NINE) && (iter_offset = -par->iter_step))
	|| ((key == NUM_PLUS || key == ZERO) && (iter_offset = par->iter_step)))
		if (iter_offset && (par->iter + iter_offset > 0))
		{
			par->iter += iter_offset;
			par->color_step = ((fl->T) ? 0xFFFFFFFF : 0xFFFFFF) / par->iter;
			redraw_fract(env);
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
		redraw_fract(env);
		return (1);
	}
	return (0);
}

int			toggles(t_env *env, int key, t_param *p, t_flags *f)
{
	if (((key == NUM_1 || key == ONE) && toggle_par(&f->n1))
		|| ((key == NUM_2 || key == TWO) && toggle_par(&f->n2))
		|| ((key == NUM_3 || key == THREE) && toggle_par(&f->n3))
		|| ((key == NUM_4 || key == FOUR) && toggle_par(&f->n4))
		|| ((key == NUM_5 || key == FIVE) && toggle_par(&f->n5))
		|| ((key == NUM_6 || key == SIX) && toggle_par(&f->n6))
		|| ((key == NUM_7 || key == SEVEN) && toggle_par(&f->n7))
		|| ((key == NUM_8 || key == EIGHT) && toggle_par(&f->n8))
		|| (key == Q && toggle_par(&f->Q)) || (key == W && toggle_par(&f->W))
		|| (key == E && toggle_par(&f->E)) || (key == T && toggle_par(&f->T)
			&& (p->color_step = ((f->T) ? 0xFFFFFFFF : 0xFFFFFF) / p->iter))
		|| (key == Y && toggle_par(&f->Y))
		|| (key == G && toggle_par(&f->G))
		|| (key == H && toggle_par(&f->Hints_on))
		|| (key == N && toggle_par(&f->Values_on))
		|| (key == M && toggle_par(&f->Menu_on)))
	{
		redraw_fract(env);
		return (1);
	}
	return (0);
}
