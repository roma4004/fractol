/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:22:29 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/09 19:29:00 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		toggle_par(int *param)
{//maybe need remove this func to ternary if
	*param = (*param == 0) ? 1 : 0;
	return (1);
}

int		deal_keyboard(int key, t_env *env)
{
	if (!env)
		return (1);
	if (!zoom(env, key, env->param->center_x, env->param->center_y))
		if (!map_offset(env, key))
			if (!iterate_change(env, key))
				if (!toggles(env, key, env->param, env->flags))
					if (specific_param(env, key))
						return (0);
	if (key == ESC)
		exit_x(env);
	else if (key == R)
	{
		env->init_func[env->param->fr_id](env->param);
		flag_reset(env->flags);
		redraw_fract(env);
	}
	else if (key == ENTER)
	{
		if (++env->param->fr_id == AMOUNT_FRACTALS)
			env->param->fr_id = 0;
		env->init_func[env->param->fr_id](env->param);
		redraw_fract(env);
	}
	else
		change_color(env, key);
	return (0);
}

int		deal_mouse(int key, int x, int y, t_env *env)
{
	if (!env)
		return (1);
	if (key == MOUSE_SCROLL_UP)
		zoom(env, PLUS, x, y);
	else if (key == MOUSE_SCROLL_DOWN)
		zoom(env, MINUS, x, y);
	else if (key == MOUSE_RBT)
		toggle_par(&env->flags->lock_julia);
	return (0);
}

int		deal_mouse_move(int x, int y, t_env *env)
{
	t_param	*p;
	t_flags	*f;

	p = env->param;
	f = env->flags;
	if (env == NULL)
		return (1);
	if (f->lock_julia)
	{
		p->seed_jI = ((double)x - p->center_x) / WIN_WIDTH - 0.7;
		p->seed_jR = ((double)y - p->center_y) / WIN_HEIGHT + 0.27015;
		redraw_fract(env);
	}
	return (0);
}
