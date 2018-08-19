/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 17:23:17 by dromanic          #+#    #+#             */
/*   Updated: 2018/08/19 16:51:04 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_fract(t_param *param, int id)
{
	param->fr_id = id;
	param->iter = (param->fr_id == FR_BARNSLEY) ? 42000 : 100;
	param->zoom = (param->fr_id == FR_BARNSLEY) ? 50 : 0.5;
	//param->color = DEF_COLOR;
	param->centr_x = WIN_WIDTH / 2;
	param->centr_y = WIN_HEIGHT / 2;
	param->zoom_x = param->zoom * param->centr_x;
	param->zoom_y = param->zoom * param->centr_y;
	//param->color_step = 0xffffff / param->iter * PI; // / 1114112;
	param->spec_step = (param->fr_id == FR_BARNSLEY) ? 0.01 : 1;
	param->offset_step = (param->fr_id == FR_BARNSLEY) ? 10 : 0.1;
	param->iter_step = (param->fr_id == FR_BARNSLEY) ? 1000 : 100;
	param->spec1 = (param->fr_id == FR_BARNSLEY) ? 0.04 : 0;
	param->spec2 = (param->fr_id == FR_BARNSLEY) ? 0.85 : 2;
	param->offset_x = (param->fr_id == FR_BARNSLEY) ? -0.5 : 0;
	param->offset_y = 0;
}

t_param	*init_param(void)
{
	t_param *new_param;

	if ((new_param = (t_param *)malloc(sizeof(t_param))))
		init_fract(new_param, FR_BARNSLEY);
	return (new_param);
}

t_flags	*init_flags(void)
{
	t_flags	*new_flags;

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

t_img	*init_img(t_win *win, int width, int height)
{
	t_img	*new_img;

	if ((new_img = (t_img *)malloc(sizeof(t_img))))
	{
		new_img->col.a = 0;
		new_img->col.r = 0;
		new_img->col.g = 0;
		new_img->col.b = 0;
		new_img->ratio = (float)WIN_WIDTH / (float)WIN_HEIGHT;
		new_img->bits_per_pixel = 0;
		new_img->size_line = 0;
		new_img->endian = 0;
		new_img->img_ptr = mlx_new_image(win->mlx_ptr, width, height);
		new_img->data = (int *)mlx_get_data_addr(new_img->img_ptr,
												&new_img->size_line,
												&new_img->bits_per_pixel,
												&new_img->endian);
	}
	return (new_img);
}

t_win	*init_win(void)
{
	t_win	*new_win;

	if (!(new_win = (t_win *)malloc(sizeof(t_win)))
		|| !(new_win->param = init_param())
		|| !(new_win->flags = init_flags())
		|| !(new_win->mlx_ptr = mlx_init())
		|| !(new_win->win_ptr =
			 mlx_new_window(new_win->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, WIN_NAME))
		|| !(new_win->img = init_img(new_win, WIN_WIDTH, WIN_HEIGHT)))
		free_win(new_win);
	return (new_win);
}
