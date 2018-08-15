/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 17:23:17 by dromanic          #+#    #+#             */
/*   Updated: 2018/08/15 19:55:14 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_fract(t_win *win)
{
	win->param->centr_x = WIN_WIDTH / 2;
	win->param->centr_y = WIN_HEIGHT / 2;
	win->param->zoom_x = win->param->zoom * win->param->centr_x;
	win->param->zoom_y = win->param->zoom * win->param->centr_y;
	if (win->param->fr_id == FR_BARNSLEY)
	{
		win->param->spec1 = DEF_BARNSLEY_CURVE_X;
		win->param->spec2 = DEF_BARNSLEY_CURVE_Y;
		win->param->color = DEF_COLOR;
		win->param->offset_step = 10;
	}
	else if (win->param->fr_id == FR_MANDELBROT)
	{
		win->param->spec1 = 0;
		win->param->spec2 = 2;
		win->param->zoom = 1;
		win->param->offset_x = -0.5;
		win->param->offset_y = 0;
		win->param->offset_step = 0.1;
		win->param->color_step = (0xffffff / win->param->iter);
		win->param->color = DEF_COLOR;
	}

}

t_param	*init_param(void)
{
	t_param *new_param;

	new_param = NULL;
	if ((new_param = (t_param *)malloc(sizeof(t_param))))
	{
		new_param->fr_id = FR_BARNSLEY;
		new_param->zoom = 0.5;
		new_param->iter = 100;
		new_param->spec1 = DEF_BARNSLEY_CURVE_X;
		new_param->spec2 = DEF_BARNSLEY_CURVE_Y;
		new_param->color = DEF_COLOR;
		new_param->color_step = 1;
		new_param->offset_step = 100;
		new_param->offset_x = DEF_OFFSET_X;
		new_param->offset_y = DEF_OFFSET_Y;
		new_param->centr_x = 0.0;
		new_param->centr_y = 0.0;
	}
	return (new_param);
}

t_flags	*init_flags(void)
{
	t_flags	*new_flags;

	new_flags = NULL;
	if ((new_flags = (t_flags *)malloc(sizeof(t_flags))))
	{
		new_flags->man_1 = 0;
		new_flags->man_2 = 0;
		new_flags->man_3 = 0;
		new_flags->man_4 = 0;
		new_flags->man_5 = 0;
		new_flags->man_6 = 0;
		new_flags->man_7 = 0;
		new_flags->interface_on = 0;
		new_flags->error_code = 0;
	}
	return (new_flags);
}

t_win	*init_win(void)
{
	t_win	*new_win;

	new_win = NULL;
	if (!(new_win = (t_win *)malloc(sizeof(t_win)))
		|| !(new_win->param = init_param())
		|| !(new_win->flags = init_flags())
		|| !(new_win->mlx_ptr = mlx_init())
		|| !(new_win->win_ptr = mlx_new_window(new_win->mlx_ptr,
											   WIN_WIDTH, WIN_HEIGHT, WIN_NAME))
		|| !(new_win->img_ptr = mlx_new_image(new_win->mlx_ptr,
											  WIN_WIDTH,
											  WIN_HEIGHT)))
		free_win(new_win);
	return (new_win);
}
