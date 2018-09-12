/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:22:29 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/12 16:26:05 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		text(t_env *env, int x, int y, char *str)
{
	if (env && str)
	{
		mlx_string_put(env->mlx_ptr, env->win_ptr, x, y,
				(env->flags->green_text) ? 0x00ff00 : DEFAULT_MENU_COLOR, str);
		if (env->flags->green_text)
			env->flags->green_text = ~env->flags->green_text;
		return (1);
	}
	return (0);
}

int		text_green(t_env *env, int x, int y, char *str)
{
	if (env && str)
	{
		mlx_string_put(env->mlx_ptr, env->win_ptr, x, y, 0x00ff00, str);
		if (env->flags->green_text)
			env->flags->green_text = ~env->flags->green_text;
		return (1);
	}
	return (0);
}

int		deal_keyboard(int key, t_env *env)
{
	if (!env || !zoom(env, key, env->param->center_x, env->param->center_y))
		if (!map_offset(env, key, env->param))
			if (!iterate_change(env, key))
				if (!toggles(env, key, env->param, env->flags))
					if (specific_param(env, key, env->param))
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
		change_color(env, key);
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
	t_param	*p;
	t_flags	*f;

	p = env->param;
	f = env->flags;
	if (env == NULL)
		return (1);
	if (f->lock_julia)
	{
		p->ij_seed = ((double)x - p->center_x) / WIN_WIDTH - 0.7;
		p->rj_seed = ((double)y - p->center_y) / WIN_HEIGHT + 0.27015;
		redraw_fract(env, 0);
	}
	return (0);
}
