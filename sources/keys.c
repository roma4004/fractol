/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:22:29 by dromanic          #+#    #+#             */
/*   Updated: 2019/04/21 21:26:51 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		exit_x(t_env *env)
{
	if (env->mlx_ptr && env->img_ptr)
	{
		mlx_destroy_image(env->mlx_ptr, env->img_ptr);
		mlx_destroy_window(env->mlx_ptr, env->win_ptr);
	}
	exit(0);
}

int		deal_keyboard(int key, t_env *env)
{
	if (!env || !zoom(env, key, env->param.center))
		if (!map_offset(env, key, env->param, &env->param.offset))
			if (!fr_depth(env, &env->param, env->flags.range, key))
				if (!toggles(env, key, &env->param, &env->flags))
					if (specific_param(env, &env->param, key))
						return (0);
	if (key == ESC)
		exit_x(env);
	if (key == R || key == ENTER)
	{
		ft_bzero(&env->flags, sizeof(t_flags));
		if (key == ENTER && ++env->param.fr_id == AMOUNT_FRACTALS)
			env->param.fr_id = 0;
		env->init_func[env->param.fr_id](&env->param);
		env->param.color_shift = (t_col_shift){ 0, 0, 0, 0 };
		env->param.threads = env->param.cores;
		env->param.hor = (env->param.fr_id == FR_FERN) ? 0.04f : 4;
		env->param.ver = (env->param.fr_id == FR_FERN) ? 0.85f : 1;
		redraw_fract_or_img(env, env->param, env->flags, 0);
	}
	else
		change_color(env, &env->param.color_shift, key);
	return (1);
}

int		deal_mouse(int key, int x, int y, t_env *env)
{
	if (!env)
		return (1);
	if (key == MOUSE_SCROLL_UP)
		zoom(env, PLUS, (t_fl_pt){ x, y });
	else if (key == MOUSE_SCROLL_DOWN)
		zoom(env, MINUS, (t_fl_pt){ x, y });
	else if (key == MOUSE_RBT)
	{
		ft_switch(&env->flags.lock_julia);
		redraw_fract_or_img(env, env->param, env->flags, 0);
	}
	return (0);
}

int		deal_mouse_move(int x, int y, t_env *env)
{
	const bool			is_julia = env->param.fr_id == FR_JULIA;
	const t_fl_pt		center = env->param.center;
	t_si_pt				mult;

	if (!env)
		return (1);
	if (x < 0 || x > W_WIDTH
	|| y < 0 || y > W_HEIGHT)
		return (0);
	mult = (t_si_pt){ (is_julia) ? 10 : 2, (is_julia) ? 10 : 4 };
	if (env->flags.lock_julia)
	{
		env->param.r_move_seed = (x - center.x) * mult.x / W_HEIGHT + 0.7;
		env->param.i_move_seed = (y - center.y) * mult.y / W_WIDTH + 0.27015;
		redraw_fract_or_img(env, env->param, env->flags, 0);
	}
	return (0);
}
