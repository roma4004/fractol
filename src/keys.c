/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:22:29 by dromanic          #+#    #+#             */
/*   Updated: 2018/08/18 20:39:28 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	deal_keyboard3(int key, t_win *win)
{
	if (key == A)
		change_color(win, 1, ALPHA_OFF);
	else if (key == Z)
		change_color(win, -1, ALPHA_OFF);
	else if (key == S)
		change_color(win, 1, RED_OFF);
	else if (key == X)
		change_color(win, -1, RED_OFF);
	else if (key == D)
		change_color(win, 1, GREEN_OFF);
	else if (key == C)
		change_color(win, -1, GREEN_OFF);
	else if (key == F)
		change_color(win, 1, BLUE_OFF);
	else if (key == V)
		change_color(win, -1, BLUE_OFF);
	return (0);
}

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
	else if (key == PAGE_UP && win->param->fr_id == FR_BARNSLEY)
		barnsley_curve(win, 0.01);
	else if (key == PAGE_DOWN && win->param->fr_id == FR_BARNSLEY)
		barnsley_curve(win, -0.01);
	else if (key == HOME && win->param->fr_id == FR_BARNSLEY)
		specific_param1(win, 0.01);
	else if (key == END && win->param->fr_id == FR_BARNSLEY)
		specific_param1(win, -0.01);
	else if (key == PAGE_UP && win->param->fr_id == FR_MANDELBROT)
		specific_param1(win, 100);
	else if (key == PAGE_DOWN && win->param->fr_id == FR_MANDELBROT)
		specific_param1(win, -100);
	else if (key == HOME && win->param->fr_id == FR_MANDELBROT)
		specific_param2(win, 1);
	else if (key == END && win->param->fr_id == FR_MANDELBROT)
		specific_param2(win, -1);
	else
		deal_keyboard3(key, win);
	return (0);
}

int			deal_keyboard(int key, t_win *win)
{
	if (!win)
		return (1);
	if (toggles(win, key))
		if (map_offset(win, key))
			if (iterate_change(win, key))
				if (zoom(win, key, win->param->centr_x, win->param->centr_y))
					deal_keyboard2(key, win);
	//printf("key %d ", key);
	return (0);
}

int			deal_mouse(int key, int x, int y, t_win *win)
{
	if (!win)
		return (1);
	//y++;
	//x++;
	if (key == MOUSE_SCROLL_UP)
		zoom(win, PLUS, x, y);
	else if (key == MOUSE_SCROLL_DOWN)
		zoom(win, MINUS, x, y);
	/*
	if (key == MOUSE_SCROLL_UP)
		zoom_offset(win, -1, 0);
	else if (key == MOUSE_SCROLL_DOWN)
		zoom_offset(win, 1, 0);
	*/
	return (0);
}
