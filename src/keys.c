/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:22:29 by dromanic          #+#    #+#             */
/*   Updated: 2018/08/30 16:25:47 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	deal_keyboard2(int key, t_win *win)
{
	if (!win)
		return (1);
	if (key == ESC)
		exit_x(win);
	else if (key == R)
		reset(win);
	else if (key == ENTER)
		fractal_switch(win);
	else if (key == ZERO)
		toggle_param(&win->flags->man_0);
	else
		change_color(win, key);
	return (0);
}

int			deal_keyboard(int key, t_win *win)
{
	//printf("key %d ", key);
	if (!win)
		return (1);
	if (!zoom(win, key, WIN_CENTER_X, WIN_CENTER_Y))
		if (!map_offset(win, key))
			if (!iterate_change(win, key))
				if (!toggles(win, key))
					if (!specific_param(win, key))
						deal_keyboard2(key, win);

	return (0);
}

int			deal_mouse(int key, int x, int y, t_win *win)
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
