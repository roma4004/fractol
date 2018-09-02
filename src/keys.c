/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:22:29 by dromanic          #+#    #+#             */
/*   Updated: 2018/08/26 16:45:19 by dromanic         ###   ########.fr       */
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
		toggle_param(&win->flags->man_0);
	else
		change_color(win, key);
	return (0);
}

int		deal_mouse(int key, int x, int y, t_env *win)
{
	if (!win)
		return (1);
	//	printf("key %d ", key);
	if (key == MOUSE_SCROLL_UP)
		zoom(win, PLUS, x, y);
	else if (key == MOUSE_SCROLL_DOWN)
		zoom(win, MINUS, x, y);
	return (0);
}
