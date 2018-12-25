/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:22:29 by dromanic          #+#    #+#             */
/*   Updated: 2018/12/25 19:00:32 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		deal_keyboard(int key, t_env *env)
{
	if (!env || !zoom(env, key, env->param->center.x, env->param->center.y))
		if (!map_offset(env, key, env->param))
			if (!fr_depth(env, env->param, env->flags, key))
				if (!toggles(env, key, env->param, env->flags))
					if (specific_param(env, env->param, key))
						return (0);
	(key == ESC) && exit_x(env);
	if (key == R || key == ENTER)
	{
		ft_bzero(env->flags, sizeof(t_flags));
		if (key == ENTER && ++env->param->fr_id == AMOUNT_FRACTALS)
			env->param->fr_id = 0;
		env->init_func[env->param->fr_id](env->param);
		env->param->col_shift.alpha = 0;
		env->param->col_shift.red = 0;
		env->param->col_shift.green = 0;
		env->param->col_shift.blue = 0;
		env->param->threads = env->param->cores;
		env->param->spec1 = (env->param->fr_id == FR_FERN) ? 0.04f : 4;
		env->param->spec2 = (env->param->fr_id == FR_FERN) ? 0.85f : 1;
		redraw_fract_or_img(env, env->param, 0);
	}
	else
		change_color(env, &env->param->col_shift, key);
	return (1);
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
	{
		env->flags->lock_julia = ~env->flags->lock_julia;
		redraw_fract_or_img(env, env->param, 0);
	}
	return (0);
}

int		deal_mouse_move(int x, int y, t_env *env)
{
	t_int_pt	mult;
	t_param		*param;
	t_flags		*flags;

	if (env == NULL)
		return (1);
	if (x < 0 || x > (int)WIN_WIDTH || y < 0 || y > (int)WIN_HEIGHT)
		return (0);
	param = env->param;
	flags = env->flags;
	mult.x = (param->fr_id == FR_JULIA) ? 10 : 2;
	mult.y = (param->fr_id == FR_JULIA) ? 10 : 4;
	if (flags->lock_julia)
	{
		param->r_mouse_move_seed =
				((x - param->center.x) * mult.x) / WIN_HEIGHT + 0.7;
		param->i_mouse_move_seed =
				((y - param->center.y) * mult.y) / WIN_WIDTH + 0.27015;
		redraw_fract_or_img(env, env->param, 0);
	}
	return (0);
}
