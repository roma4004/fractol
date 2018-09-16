/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 12:29:00 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/16 16:45:49 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "main.h"

void		px_to_img(t_img *img, int x, int y, int color)
{
	if (img
		&& x >= 0 && x < (int)WIN_WIDTH
		&& y >= 0 && y < (int)WIN_HEIGHT)
		img->data[y * (int)WIN_WIDTH + x] = color;
}

static void	*draw_threads(void *thread_data)
{
	int			x;
	int			y;
	t_env		*env;
	t_param		*param;
	t_pth_dt	*data;

	if (!thread_data)
		return (NULL);
	data = (t_pth_dt *)thread_data;
	env = data->env;
	param = env->param;
	y = (int)((param->center_y * -1) / param->actial_zoom);
	while (y < (int)WIN_HEIGHT)
	{
		x = (int)((param->center_x * -1) / param->actial_zoom);
		while (x < (int)WIN_WIDTH)
		{
			px_to_img(env->img, x, y + data->offset,
					get_fractal_color(param, env->flags, x, y + data->offset));
			x++;
		}
		y += param->threads;
	}
	return (NULL);
}

void		parallel_draw_fractal(t_env *env)
{
	int			id;
	int			cpu_cores;
	t_pth_dt	*data;
	pthread_t	*threads;

	if (!env)
		return ;
	cpu_cores = env->param->threads;
	threads = (pthread_t *)malloc(sizeof(pthread_t) * cpu_cores);
	data = (t_pth_dt *)malloc(sizeof(t_pth_dt) * cpu_cores);
	id = -1;
	while (++id < cpu_cores)
	{
		data[id].env = env;
		data[id].offset = id;
		pthread_create(&threads[id], NULL, draw_threads, &data[id]);
	}
	id = -1;
	while (++id < cpu_cores)
		pthread_join(threads[id], NULL);
	redraw_fract(env, 1);
	argb_shift(env, env->param);
	ft_memdel((void *)&threads);
	ft_memdel((void *)&data);
}
