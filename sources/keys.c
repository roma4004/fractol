/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:22:29 by dromanic          #+#    #+#             */
/*   Updated: 2019/01/01 18:15:30 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		exit_x(t_env *env)
{
	mlx_destroy_window(env->mlx_ptr, env->win_ptr);
	free_win(env);
	exit(0);
}

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
		env->param->hor = (env->param->fr_id == FR_FERN) ? 0.04f : 4;
		env->param->ver = (env->param->fr_id == FR_FERN) ? 0.85f : 1;
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
		ft_switch(&env->flags->lock_julia);
		redraw_fract_or_img(env, env->param, 0);
	}
	return (0);
}

int		deal_mouse_move(int x, int y, t_env *env)
{
	t_int_pt	mult;
	t_param		*p;
	t_flags		*flags;

	if (env == NULL)
		return (1);
	if (x < 0 || x > (int)W_WIDTH || y < 0 || y > (int)W_HEIGHT)
		return (0);
	p = env->param;
	flags = env->flags;
	mult.x = (p->fr_id == FR_JULIA) ? 10 : 2;
	mult.y = (p->fr_id == FR_JULIA) ? 10 : 4;
	if (flags->lock_julia)
	{
		p->r_move_seed = (x - p->center.x) * mult.x / W_HEIGHT + 0.7;
		p->i_move_seed = (y - p->center.y) * mult.y / W_WIDTH + 0.27015;
		redraw_fract_or_img(env, p, 0);
	}
	return (0);
}
