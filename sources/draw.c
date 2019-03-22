/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 20:43:55 by dromanic          #+#    #+#             */
/*   Updated: 2019/03/22 18:34:01 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "main.h"

static void		set_px(unsigned int *surface, int x, int y, unsigned int color)
{
	if (x >= 0 && x < W_WIDTH && y >= 0 && y < W_HEIGHT)
		surface[y * W_WIDTH + x] = color;
}

unsigned int	draw_barnsley(t_env *env, t_param *p, int x, int y)
{
	float		random_num;
	long long	px_cnt;
	t_fern		fern;
	t_fern		tmp;

	fern = (t_fern){.r = x, .i = y};
	px_cnt = p->depth;
	while (px_cnt-- && (random_num = (float)rand() / RAND_MAX))
	{
		tmp = fern;
		if (random_num <= .01f)
			fern = (t_fern){.r = 0, .i = .16f * tmp.i};
		else if (random_num <= .06f)
			fern = (t_fern){.r = -.15f * tmp.r + .28f * tmp.i,
							.i = .26f * tmp.r + .24f * tmp.i + .44f};
		else if (random_num <= .14f)
			fern = (t_fern){.r = .2f * tmp.r + -.26f * tmp.i,
							.i = .23f * tmp.r + .22f * tmp.i + 1.6f};
		else
			fern = (t_fern){.r = .85 * tmp.r + p->hor * tmp.i,
							.i = -.04 * tmp.r + p->ver * tmp.i + 1.6};
		set_px(env->surface, (int)(fern.r * p->actial_zoom - p->offset.x),
			(int)(W_HEIGHT - fern.i * p->actial_zoom - p->offset.y), 0x007700);
	}
	return (redraw_fract_or_img(env, p, 1));
}

static void		*draw_threads(void *thread_data)
{
	int			x;
	int			y;
	int			offset;
	t_env		*env;
	t_param		*p;

	if (!thread_data)
		return (NULL);
	offset = ((t_pth_dt *)thread_data)->offset;
	env = ((t_pth_dt *)thread_data)->env;
	p = env->param;
	y = -1;
	while (++y < W_HEIGHT)
	{
		x = 0;
		while (x < W_WIDTH)
		{
			x += offset;
			set_px(env->surface, x, y, env->get_px[p->fr_id](env, p, x, y));
			x -= offset;
			x += p->threads;
		}
	}
	return (NULL);
}

void			parallel_draw(t_env *env, unsigned int threads)
{
	unsigned int	id;
	t_pth_dt		*data;
	pthread_t		*threads_arr;

	if (!env || !(data = (t_pth_dt *)malloc(threads * sizeof(t_pth_dt))))
		return ;
	if (!(threads_arr = (pthread_t *)malloc(threads * sizeof(pthread_t))))
	{
		free(data);
		return ;
	}
	id = UINT32_MAX;
	while (++id < threads)
	{
		data[id].env = env;
		data[id].offset = id;
		pthread_create(&threads_arr[id], NULL, draw_threads, &data[id]);
	}
	id = UINT32_MAX;
	while (++id < threads)
		pthread_join(threads_arr[id], NULL);
	redraw_fract_or_img(env, env->param, 1);
	argb_shift(env, &env->param->col_shift);
	free(data);
	free(threads_arr);
}
