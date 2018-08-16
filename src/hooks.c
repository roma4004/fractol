/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 15:18:37 by dromanic          #+#    #+#             */
/*   Updated: 2018/08/16 17:26:37 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		exit_x(t_win *win)
{
	mlx_destroy_window(win->mlx_ptr, win->win_ptr);
	free_win(win);
	exit(0);
}

void	map_offset(t_win *win, double offset_x, double offset_y)
{
	win->param->offset_x += offset_x;
	win->param->offset_y += offset_y;
	redraw_fract(win);
}

void	specific_param2(t_win *win, double spec2_offset)
{
	win->param->spec2 += spec2_offset;
	redraw_fract(win);
	printf("specific_param2 %f\n", win->param->spec2);
}

void	specific_param1(t_win *win, double spec1_offset)
{
	win->param->spec1 += spec1_offset;
	redraw_fract(win);
	printf("specific_param1 %f\n", win->param->spec1);
}

void	barnsley_curve(t_win *win, double spec2_offset)
{
		win->param->spec2 += spec2_offset;
	redraw_fract(win);
	printf("barnsley_curve %f\n", win->param->spec2);
}

void	iterate_change(t_win *win, int iter_offset)
{
	if (win->param->iter + iter_offset >= 0)
		win->param->iter += iter_offset;
	redraw_fract(win);
	printf("iter ch %d\n", win->param->iter);
}

void	fr_zoom(t_win *win, float offset, int x, int y)
{
	if (win->param->zoom + offset > 0)
	{
		win->param->zoom += offset;
		win->param->zoom_x = win->param->zoom * win->param->centr_x;
		win->param->zoom_y = win->param->zoom * win->param->centr_y;
	}
	printf("%f\n",win->param->zoom);
	//x++;
	//y++;
	win->param->offset_x += (x - WIN_WIDTH / 2) / (win->param->zoom * WIN_WIDTH);
	win->param->offset_y += (y - WIN_HEIGHT / 2) / (win->param->zoom * WIN_HEIGHT);
	//or
	//win->param->offset_x += (x - WIN_WIDTH / 2) / ((WIN_WIDTH / 2) * win->param->zoom);
	//win->param->offset_y += (y - WIN_HEIGHT / 2) / ((WIN_HEIGHT / 2) * win->param->zoom);
	redraw_fract(win);
}

void	fractal_switch(t_win *win)
{
	mlx_clear_window(win->mlx_ptr, win->win_ptr);
	//if (win->flags->interface_on)
	//	show_interface(win);
	if (++win->param->fr_id == 3)
		win->param->fr_id = 0;
	redraw_fract(win);
}

void	toggles(t_win *win, int key)
{
	if (key == 1)
		toggle_param(&win->flags->man_1);
	if (key == 2)
		toggle_param(&win->flags->man_2);
	if (key == 3)
		toggle_param(&win->flags->man_3);
	if (key == 4)
		toggle_param(&win->flags->man_4);
	if (key == 5)
		toggle_param(&win->flags->man_5);
	if (key == 6)
		toggle_param(&win->flags->man_6);
	if (key == 7)
		toggle_param(&win->flags->man_7);
	if (key == 8)
		toggle_param(&win->flags->interface_on);
	redraw_fract(win);
}

void		reset(t_win *win)
{
	//size_t	y;
	//size_t	x;

	if (!win)
		return ;
	/*y = -1;
	while (++y < win->param->rows)
	{
		x = -1;
		while (++x < win->param->cols)
		{
			win->map[y][x].x = x;
			win->map[y][x].y = y;
			win->map[y][x].z = win->map[y][x].z_orig;
		}
	}*/

	if (win->param->fr_id == FR_BARNSLEY)
	{
		win->param->spec1 = DEF_BARNSLEY_CURVE_X;
		win->param->spec2 = DEF_BARNSLEY_CURVE_Y;

	}
	win->param->offset_x = DEF_OFFSET_X;
	win->param->offset_y = DEF_OFFSET_Y;
	redraw_fract(win);
}
