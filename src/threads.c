/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 12:29:00 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/22 19:38:20 by dromanic         ###   ########.fr       */
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
	int			offset;
	t_env		*env;
	t_param		*param;

	if (!thread_data)
		return (NULL);
	offset = ((t_pth_dt *)thread_data)->offset;
	env = ((t_pth_dt *)thread_data)->env;
	param = env->param;
	y = 0;
	while (++y < (int)WIN_HEIGHT)
	{
		x = 0;
		while (x < (int)WIN_WIDTH)
		{
			px_to_img(env->img, x + offset, y,
					get_fractal_color(param, env->flags, x + offset, y));
			x += param->threads;
		}
	}
	return (NULL);
}

void		parallel_draw(t_env *env, int threads)
{
	int			id;
	t_pth_dt	data[threads];
	pthread_t	threads_arr[threads];

	if (!env)
		return ;
	id = -1;
	while (++id < threads)
	{
		data[id].env = env;
		data[id].offset = id;
		pthread_create(&threads_arr[id], NULL, draw_threads, &data[id]);
	}
	id = -1;
	while (++id < threads)
		pthread_join(threads_arr[id], NULL);
	redraw_fract_or_img(env, 1);
	argb_shift(env, env->param);
}
