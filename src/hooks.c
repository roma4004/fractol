/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 15:18:37 by dromanic          #+#    #+#             */
/*   Updated: 2018/08/18 20:41:08 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	change_color(t_win *win, int offset, int chanel)
{
	int		y;
	int		x;
	int		px;
	t_img	*img;

	img = win->img;
	y = -1;
	while(++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			px = y * WIN_WIDTH + x;
			img->data[px] = change_hue(img->data[px], offset, chanel);
		}
	}
	mlx_clear_window(win->mlx_ptr, win->win_ptr);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, img->img_ptr, 0, 0);
}

int		exit_x(t_win *win)
{
	mlx_destroy_window(win->mlx_ptr, win->win_ptr);
	free_win(win);
	exit(0);
}

static void	set_color(int *chanel, int offset)
{
	if (*chanel + offset > 0 || *chanel < 256)
		*chanel += offset;
}

void	color_offset(t_win *win, int offset, char type)
{
	if (type == 'a' || type == 'A') set_color(&win->img->col.a, offset);
	if (type == 'r' || type == 'R') set_color(&win->img->col.r, offset);
	if (type == 'g' || type == 'G') set_color(&win->img->col.g, offset);
	if (type == 'b' || type == 'B') set_color(&win->img->col.b, offset);
}

int		map_offset(t_win *win, int key)
{
	int		need_redraw;
	double	offset_x;
	double	offset_y;

	need_redraw = 0;
	offset_x = 0;
	offset_y = 0;
	if (key == ARROW_LEFT && (need_redraw = 1))
		offset_x = win->param->offset_step;
	else if (key == ARROW_UP && (need_redraw = 1))
		offset_y = win->param->offset_step;
	else if (key == ARROW_DOWN && (need_redraw = 1))
		offset_y = -win->param->offset_step;
	else if (key == ARROW_RIGHT && (need_redraw = 1))
		offset_x = -win->param->offset_step;
	if (need_redraw)
	{
		win->param->offset_x += offset_x;
		win->param->offset_y += offset_y;
		redraw_fract(win);
		return (0);
	}
	return (1);
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

int		iterate_change(t_win *win, int key)
{
	int iter_offset;
	int need_redraw;

	iter_offset = 0;
	need_redraw = 0;
	if ((key == NUM_MINUS || key == NINE) && (need_redraw = 1))
		iter_offset = -win->param->iter_step;
	else if ((key == NUM_PLUS || key == ZERO) && (need_redraw = 1))
		iter_offset = win->param->iter_step;
	if (win->param->iter + iter_offset >= 0)
		win->param->iter += iter_offset;
	if ((need_redraw) && (win->param->iter + iter_offset >= 0))
	{
		win->param->iter += iter_offset;
		redraw_fract(win);
		return (0);
	}
	return (1);
	printf("iter ch %d\n", win->param->iter);
}

int		zoom(t_win *win, int key, float x, float y)
{
	double	zoom_factor;
	int		need_redraw;

	need_redraw = 0;
	zoom_factor = 0;
	if (key == MINUS && (need_redraw = 1))
		zoom_factor = -0.5;
	else if (key == PLUS && (need_redraw = 1))
		zoom_factor = 0.5;
	if (need_redraw && win->param->zoom + zoom_factor > 0)
	{
		win->param->zoom += zoom_factor;
		win->param->zoom_x = win->param->zoom * win->param->centr_x;
		win->param->zoom_y = win->param->zoom * win->param->centr_y;
		win->param->offset_x += (x - WIN_WIDTH / 2) / (win->param->zoom * WIN_WIDTH);
		win->param->offset_y += (y - WIN_HEIGHT / 2) / (win->param->zoom * WIN_HEIGHT);
		printf("%f\n",win->param->zoom);
		redraw_fract(win);
		//or
		//win->param->offset_x += (x - WIN_WIDTH / 2) / ((WIN_WIDTH / 2) * win->param->zoom);
		//win->param->offset_y += (y - WIN_HEIGHT / 2) / ((WIN_HEIGHT / 2) * win->param->zoom);
	}
	return (1);
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

int		toggles(t_win *win, int key)
{
	int need_redraw;

	need_redraw = 0;
	if (key == NUM_1 || key == ONE)
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
		return (0);
	}
	return (1);
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
