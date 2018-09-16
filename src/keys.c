/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:22:29 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/16 17:10:02 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*text(t_env *env, int x, int y, char *str)
{
	if (env && str)
	{
		mlx_string_put(env->mlx_ptr, env->win_ptr, x, y,
				(env->flags->green_text) ? 0x00ff00 : DEFAULT_MENU_COLOR, str);
		if (env->flags->green_text)
			env->flags->green_text = ~env->flags->green_text;
		return (str);
	}
	return (NULL);
}

char	*text_green(t_env *env, int x, int y, char *str)
{
	if (env && str)
	{
		mlx_string_put(env->mlx_ptr, env->win_ptr, x, y, 0x00ff00, str);
		if (env->flags->green_text)
			env->flags->green_text = ~env->flags->green_text;
		return (str);
	}
	return (NULL);
}

int		deal_keyboard(int key, t_env *env)
{
	if (!env || !zoom(env, key, env->param->center_x, env->param->center_y))
		if (!map_offset(env, key, env->param))
			if (!fr_depth(env, env->param, env->flags, key))
				if (!toggles(env, key, env->param, env->flags))
					if (specific_param(env, env->param, key))
						return (0);
	(key == ESC) && exit_x(env);
	if ((key == R || key == ENTER) && flag_reset(env->flags))
	{
		if (key == ENTER && ++env->param->fr_id == AMOUNT_FRACTALS)
			env->param->fr_id = 0;
		env->init_func[env->param->fr_id](env->param);
		env->param->alpha_shift = 0;
		env->param->red_shift = 0;
		env->param->green_shift = 0;
		env->param->blue_shift = 0;
		env->param->threads = env->param->cores;
		env->param->spec1 = (env->param->fr_id == FR_BARNSLEY) ? 0.04f : 4;
		env->param->spec2 = (env->param->fr_id == FR_BARNSLEY) ? 0.85f : 1;
		redraw_fract(env, 0);
	}
	else
		change_color(env, env->param, key);
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
		redraw_fract(env, 0);
	}
	return (0);
}

int		deal_mouse_move(int x, int y, t_env *env)
{
	int		mult_x;
	int		mult_y;
	t_param	*param;
	t_flags	*flags;

	if (env == NULL)
		return (1);
	if (x < 0 || x > (int)WIN_WIDTH || y < 0 || y > (int)WIN_HEIGHT)
		return (0);
	param = env->param;
	flags = env->flags;
	mult_x = (param->fr_id == FR_JULIA) ? 10 : 2;
	mult_y = (param->fr_id == FR_JULIA) ? 20 : 4;
	if (flags->lock_julia)
	{
		param->r_mouse_move_seed =
				((x - param->center_x) * mult_x) / WIN_HEIGHT + 0.7;
		param->i_mouse_move_seed =
				((y - param->center_y) * mult_y) / WIN_WIDTH + 0.27015;
		redraw_fract(env, 0);
	}
	return (0);
}
