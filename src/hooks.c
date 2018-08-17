/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 15:18:37 by dromanic          #+#    #+#             */
/*   Updated: 2018/08/17 22:16:22 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	change_color(t_win *win)
{
	t_coords indexs;
	//	t_cnb   c;
	int		px_addr;
	//int		color;
	int		i;

	indexs.y = -1;
	while(++indexs.y < WIN_HEIGHT)
	{
		indexs.x = -1;
		while (++indexs.x < WIN_WIDTH)
		{
			//use color model conversion to get rainbow palette, make brightness black if maxIterations reached
			//color = HSVtoRGB(ColorHSV(i % 256, 255, 255 * (i < maxIterations)));

			//i = get_fractal_point(win, &indexs);
			//gen_color(win, i);
			//win->param->color =(i *(x+y) / win->param->iter) * (newRe * newIm);
			px_addr = indexs.y * WIN_WIDTH + indexs.x;
			//			int RGB = (alpha << 24);
			//			RGB = RGB | (red << 16);
			//			RGB = RGB | (green << 8);
			//			RGB = RGB | (blue);

			//			color = ( (win->img->col.a) << 24)
			//					| ((win->img->col.r) << 16)
			//					| ((win->img->col.g) << 8)
			//					| ( win->img->col.b);

			///win->img->data[px_addr] = get_color(gen_color(win, i));
			win->img->data[px_addr] = inc_color(win->img->data[px_addr], RED_OFF);
}

int		exit_x(t_win *win)
{
	mlx_destroy_window(win->mlx_ptr, win->win_ptr);
	free_win(win);
	exit(0);
}

void	set_color(int *color_part, int offset)
{
	if (*color_part + offset > 0 || *color_part < 256)
		*color_part += offset;
}

void	color_offset(t_win *win, int offset, char type)
{
	if (type == 'a' || type == 'A') set_color(&win->img->col.a, offset);
	if (type == 'r' || type == 'R') set_color(&win->img->col.r, offset);
	if (type == 'g' || type == 'G') set_color(&win->img->col.g, offset);
	if (type == 'b' || type == 'B') set_color(&win->img->col.b, offset);
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
