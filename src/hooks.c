/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 15:18:37 by dromanic          #+#    #+#             */
/*   Updated: 2018/08/30 18:15:23 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		change_color(t_win *win, int key)
{
	int		y;
	int		x;
	int		offset;
	int		chanel;

	offset = 0;
	if (key == G && toggle_param(&win->flags->color_type))
		return ;
	if ((key == A || (key == Z)) && (chanel = ALPHA))
		offset = (key == A) ? 1 : -1;
	else if ((key == S || (key == X)) && (chanel = RED))
		offset = (key == S) ? 1 : -1;
	else if ((key == D || (key == C)) && (chanel = GREEN))
		offset = (key == D) ? 1 : -1;
	else if ((key == F || (key == V)) && !(chanel = BLUE))
		offset = (key == F) ? 1 : -1;
	if (offset && (y = -1))
	{
		while (++y < WIN_HEIGHT && (x = -1))
			while (++x < WIN_WIDTH)
				win->img->data[y * (int)WIN_WIDTH + x] =
				change_hue(win->img->data[y * (int)WIN_WIDTH + x], offset, chanel);
		redraw_img(win);
	}
}

int			map_offset(t_win *win, int key)
{
	int		need_redraw;
	double	offset_x;
	double	offset_y;
	t_param *par;

	par = win->param;
	need_redraw = 0;
	offset_x = 0;
	offset_y = 0;
	if (key == ARROW_LEFT && (need_redraw = 1))
		offset_x = par->offset_step;
	else if (key == ARROW_UP && (need_redraw = 1))
		offset_y = par->offset_step;
	else if (key == ARROW_DOWN && (need_redraw = 1))
		offset_y = -par->offset_step;
	else if (key == ARROW_RIGHT && (need_redraw = 1))
		offset_x = -par->offset_step;
	if (need_redraw)
	{
		par->offset_x += offset_x;
		par->offset_y += offset_y;
		redraw_fract(win);
		return (1);
	}
	return (0);
}

int			specific_param(t_win *win, int key)
{
	int		need_redraw;
	t_param *param;

	param = win->param;
	need_redraw = 0;
	if ((key == PAGE_UP || key == PAGE_DOWN) && (need_redraw = 1))
		param->spec2 += (key == PAGE_UP) ? param->spec_step : -param->spec_step;
	else if ((key == HOME || key == END) && (need_redraw = 1))
		param->spec1 += (key == HOME) ? -param->spec_step : param->spec_step;
	if (need_redraw)
	{
		redraw_fract(win);
		return (1);
	}
	return (0);
}

int			iterate_change(t_win *win, int key)
{
	int		iter_offset;
	int		need_redraw;
	t_param *param;

	param = win->param;printf("iter ch %d\n", param->iter);
	iter_offset = 0;
	need_redraw = 0;
	if ((key == NUM_MINUS || key == NINE) && (need_redraw = 1))
		iter_offset = -param->iter_step;
	else if ((key == NUM_PLUS || key == ZERO) && (need_redraw = 1))
		iter_offset = param->iter_step;
	if ((need_redraw) && (param->iter + iter_offset > 0))
	{
		param->iter += iter_offset;
		param->color_step = 0xFFFFFFFF / param->iter;
		redraw_fract(win);
		return (1);
	}
	return (0);

}

int			zoom(t_win *win, int key, float x, float y)
{
	t_param	*param;

	param = win->param;
	if (key == MINUS || key == PLUS)
	{
//		printf("%f\n", param->zoom);
		if (key == MINUS && (param->zoom / 1.4) < 10)
			return (0);
		param->zoom = (key == PLUS) ? param->zoom * 1.4 : param->zoom / 1.4;
		param->zoom_x = (x - WIN_CENTER_X) / (param->zoom * WIN_WIDTH);
		param->zoom_y = (y - WIN_CENTER_Y) / (param->zoom * WIN_HEIGHT);
		param->offset_x += 0.1 / param->zoom;
		param->offset_y += 0.1 / param->zoom;
		x++; y++;
//		param->offset_x += (x - WIN_WIDTH / 2) / (param->zoom * WIN_WIDTH);
//		param->offset_y += (y - WIN_HEIGHT / 2) / (param->zoom * WIN_HEIGHT);

		redraw_fract(win);
		//or
		// win->param->offset_x += (x - WIN_WIDTH / 2)
		// 							/ ((WIN_WIDTH / 2) * win->param->zoom);
		//win->param->offset_y += (y - WIN_HEIGHT / 2)
		// 							/ ((WIN_HEIGHT / 2) * win->param->zoom);
		return (1);
	}
	return (0);
}

void		fractal_switch(t_win *win)
{
	mlx_clear_window(win->mlx_ptr, win->win_ptr);
	//if (win->flags->interface_on)
	//	show_interface(win);
	if (++win->param->fr_id == 2)
		win->param->fr_id = 0;
	init_fract(win->param, win->param->fr_id);
	redraw_fract(win);
}

int			toggles(t_win *win, int key)
{
	int need_redraw;

	need_redraw = 0;
	if ((key == NUM_1 || key == ONE) && (need_redraw = 1))
		toggle_param(&win->flags->man_1);
	else if ((key == NUM_2 || key == TWO) && (need_redraw = 1))
		toggle_param(&win->flags->man_2);
	else if ((key == NUM_3 || key == THREE) && (need_redraw = 1))
		toggle_param(&win->flags->man_3);
	else if ((key == NUM_4 || key == FOUR) && (need_redraw = 1))
		toggle_param(&win->flags->man_4);
	else if ((key == NUM_5 || key == FIVE) && (need_redraw = 1))
		toggle_param(&win->flags->man_5);
	else if ((key == NUM_6 || key == SIX) && (need_redraw = 1))
		toggle_param(&win->flags->man_6);
	else if ((key == NUM_7 || key == SEVEN) && (need_redraw = 1))
		toggle_param(&win->flags->man_7);
	else if ((key == NUM_8 || key == EIGHT) && (need_redraw = 1))
		toggle_param(&win->flags->interface_on);
	if (need_redraw)
	{
		redraw_fract(win);
		return (1);
	}
	return (0);
}

void		reset(t_win *win)
{
	if (!win)
		return ;
	init_fract(win->param, win->param->fr_id);
	//need to reset flags
	redraw_fract(win);
}
