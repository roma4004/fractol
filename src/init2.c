/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 17:57:00 by dromanic          #+#    #+#             */
/*   Updated: 2018/08/23 15:45:17 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		init_fract(t_param *param, int id)
{
	param->fr_id = id;
	param->iter = (param->fr_id == FR_BARNSLEY) ? 42000 : 100;
	param->zoom = (param->fr_id == FR_BARNSLEY) ? 50 : 0.5;
	//param->color = DEF_COLOR;
	param->centr_x = WIN_WIDTH / 2;
	param->centr_y = WIN_HEIGHT / 2;
	param->color_step = 0xFFFFFFFF / param->iter;
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


t_img	*init_img(void *mlx_ptr, int width, int height)
{
	t_img	*new_img;

	if (!mlx_ptr)
		return (NULL);
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
		new_img->img_ptr = mlx_new_image(mlx_ptr, width, height);
		new_img->data = (int *)mlx_get_data_addr(new_img->img_ptr,
												 &new_img->size_line,
												 &new_img->bits_per_pixel,
												 &new_img->endian);
	}
	return (new_img);
}

t_pth_dt	*init_pthread_dt(t_win *win, int id)
{
	t_pth_dt	*new_pthread_data;

	if (!win)
		return (NULL);
	if ((new_pthread_data = (t_pth_dt *)malloc(sizeof(t_pth_dt))))
	{
		new_pthread_data->win = win;
		new_pthread_data->id = id;
	}
	return (new_pthread_data);
}

pthread_t	*init_pthreads(t_win *win)
{
	pthread_t	*new_pthread;

	if (!win)
		return (NULL);
	if ((new_pthread =
		 (pthread_t *)malloc(sizeof(pthread_t) * win->param->cpu_cores)))
	{
		return (new_pthread);
	}
	return (new_pthread);
}

