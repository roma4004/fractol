/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:22:29 by dromanic          #+#    #+#             */
/*   Updated: 2018/08/14 19:04:38 by jdoeanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	deal_keyboard3(int key, t_win *win)
{
	if (!win)
		return (1);
	if (key == ESC)
		exit_x(win);
//	else if (key == Q) rotate_map(win, 'y', 2);
//	else if (key == W) rotate_map(win, 'x', 2);
//	else if (key == E) rotate_map(win, 'z', 2);
//	else if (key == A) rotate_map(win, 'y', -2);
//	else if (key == S) rotate_map(win, 'x', -2);
//	else if (key == D) rotate_map(win, 'z', -2);
	else if (key == R)
		reset(win);
	return (0);
}

static int	deal_keyboard2(int key, t_win *win)
{
	if (!win)
		return (1);
	if (key == NUM_1 || key == ONE)
		toggles(win, 1);
	else if (key == NUM_2 || key == TWO)
		toggles(win, 2);
	else if (key == NUM_3 || key == THREE)
		toggles(win, 3);
	else if (key == NUM_4 || key == FOUR)
		toggles(win, 4);
	else if (key == NUM_5 || key == FIVE)
		toggles(win, 5);
	else if (key == NUM_6 || key == SIX)
		toggles(win, 6);
	else if (key == NUM_7 || key == SEVEN)
		toggles(win, 7);
	else if (key == NUM_8 || key == EIGHT)
		toggles(win, 8);
	else
		deal_keyboard3(key, win);
	return (0);
}

int			deal_keyboard(int key, t_win *win)
{
	if (!win)
	{
		return (1);
	}
	printf("key %d\n", key);
	if (key == ARROW_LEFT)
		map_offset(win, win->param->offset_step, 0);
	else if (key == ARROW_UP)
		map_offset(win, 0, win->param->offset_step);
	else if (key == ARROW_DOWN)
		map_offset(win, 0, -win->param->offset_step);
	else if (key == ARROW_RIGHT)
		map_offset(win, -win->param->offset_step, 0);
	else if (key == NUM_MINUS || key == NINE)
		iterate_change(win, -1000);
	else if (key == NUM_PLUS || key == ZERO)
		iterate_change(win, +1000);
	else if (key == ENTER)
		fractal_switch(win);
	else if (key == MINUS)
		fr_zoom(win, -0.5, win->param->centr_x, win->param->centr_y);
	else if (key == PLUS)
		fr_zoom(win, 0.5, win->param->centr_x, win->param->centr_y);
	else if (key == 116 && win->param->fr_id == FR_BARNSLEY)
		barnsley_curve(win, 0.01);
	else if (key == 121 && win->param->fr_id == FR_BARNSLEY)
		barnsley_curve(win, -0.01);
	else if (key == 115 && win->param->fr_id == FR_BARNSLEY)
		specific_param1(win, 0.01);
	else if (key == 119 && win->param->fr_id == FR_BARNSLEY)
		specific_param1(win, -0.01);
	else if (key == 116 && win->param->fr_id == FR_MANDELBROT)
		specific_param1(win, 100);
	else if (key == 121 && win->param->fr_id == FR_MANDELBROT)
		specific_param1(win, -100);
	else if (key == 115 && win->param->fr_id == FR_MANDELBROT)
		specific_param2(win, 1);
	else if (key == 119 && win->param->fr_id == FR_MANDELBROT)
		specific_param2(win, -1);
	else
		deal_keyboard2(key, win);
	return (0);
}

int			deal_mouse(int key, int x, int y, t_win *win)
{
	if (!win)
		return (1);
	y++;
	x++;

	if (key == MOUSE_SCROLL_UP)
		fr_zoom(win, 0.5, x, y);
	else if (key == MOUSE_SCROLL_DOWN)
		fr_zoom(win, -0.5, x, y);
	/*
	if (key == MOUSE_SCROLL_UP)
		zoom_offset(win, -1, 0);
	else if (key == MOUSE_SCROLL_DOWN)
		zoom_offset(win, 1, 0);
	*/
	return (0);
}
