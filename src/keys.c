/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:22:29 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/06 20:31:11 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		deal_keyboard(int key, t_env *win)
{
	//printf("key %d ", key);
	if (!win)
		return (1);
	if (!zoom(win, key, win->param->center_x, win->param->center_y))
		if (!map_offset(win, key))
			if (!iterate_change(win, key))
				if (!toggles(win, key))
					if (specific_param(win, key))
						return (0);
	if (key == ESC)
		exit_x(win);
	else if (key == R)
	{
		win->init_func[win->param->fr_id](win->param);//todo: need to reset flags
		redraw_fract(win);
	}
	else if (key == ENTER)
	{
		if (++win->param->fr_id == AMOUNT_FRACTALS)
			win->param->fr_id = 0;
		win->init_func[win->param->fr_id](win->param);
		redraw_fract(win);
	}
	else if (key == ZERO)
		toggle_param(&win->flags->n0);
	else
		change_color(win, key);
	return (0);
}

int		deal_mouse(int key, int x, int y, t_env *win)
{
	if (!win)
		return (1);
	printf("key %d ", key);
	if (key == MOUSE_SCROLL_UP)
		zoom(win, PLUS, x, y);
	else if (key == MOUSE_SCROLL_DOWN)
		zoom(win, MINUS, x, y);
	else if (key == 1)
		toggle_param(&win->flags->lock_julia);
	return (0);
}

int		deal_mouse_move(int x, int y, t_env *win)
{
	t_param *p;
	t_flags *f;

	p = win->param;
	f = win->flags;
	if (!win)
		return (1);

	if (win->param->fr_id == FR_JULIA &&f->lock_julia)
	{
		win->param->seed_jI = ((double)x - win->param->center_x) / WIN_WIDTH - 0.7;
		win->param->seed_jR = ((double)y - win->param->center_y) / WIN_HEIGHT + 0.27015;
		redraw_fract(win);
//		jR = -0.7;
//		jI = 0.27015;
	}
	return (0);
}
