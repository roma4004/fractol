/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 20:43:55 by dromanic          #+#    #+#             */
/*   Updated: 2019/06/25 15:41:39 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "main.h"

static inline void		set_px(unsigned int *restrict surface,
								unsigned int color, size_t x, size_t y)
{
	if (W_HEIGHT > y && W_WIDTH > x)
		surface[y * W_WIDTH + x] = color;
}

unsigned int			draw_barnsley(t_env const *restrict env, t_param p,
										size_t x, size_t y)
{
	t_fern		fern;
	t_fern		tmp;
	float		random_num;

	fern = (t_fern){ .r = x, .i = y };
	while (--(p.depth))
	{
		random_num = (float)(rand()) / RAND_MAX;
		tmp = fern;
		if (0.01f >= random_num)
			fern = (t_fern){ .r = 0, .i = 0.16 * tmp.i };
		else if (0.06f >= random_num)
			fern = (t_fern){ .r = -0.15 * tmp.r + 0.28 * tmp.i,
							.i = 0.26 * tmp.r + 0.24 * tmp.i + 0.44 };
		else if (0.14f >= random_num)
			fern = (t_fern){ .r = 0.2 * tmp.r + -0.26 * tmp.i,
							.i = 0.23 * tmp.r + 0.22 * tmp.i + 1.6 };
		else
			fern = (t_fern){ .r = 0.85 * tmp.r + p.hor * tmp.i,
							.i = -0.04 * tmp.r + p.ver * tmp.i + 1.6 };
		set_px(env->surf, 0x7700, (size_t)(fern.r * 50 - 300),
					(size_t)(W_HEIGHT - fern.i * 50 - 300));
	}
	return (redraw_fract_or_img(env, p, env->flags, 1));
}

static void				*draw_threads(void *restrict thread_data)
{
	register const size_t		offset = ((t_pth_dt *)thread_data)->offset;
	const t_env					*env = ((t_pth_dt *)thread_data)->env;
	const t_param				p = env->param;
	register size_t				x;
	register size_t				y;

	y = W_HEIGHT;
	while (y--)
	{
		x = 1 + UINT64_MAX - p.threads;
		while ((x += p.threads) < W_WIDTH)
			set_px(env->surf, env->get_px_func[p.fr_id](env, p, x + offset, y),
																x + offset, y);
	}
	return (NULL);
}

void					parallel_draw(t_env const *restrict env,
										unsigned int threads)
{
	register unsigned int	id;
	t_pth_dt				*data;
	pthread_t				*threads_arr;

	if (!env || !(data = (t_pth_dt *)malloc(threads * sizeof(t_pth_dt))))
		return ;
	if (!(threads_arr = (pthread_t *)malloc(threads * sizeof(pthread_t))))
	{
		free(data);
		return ;
	}
	id = UINT32_MAX;
	while (threads > ++id)
	{
		data[id] = (t_pth_dt){ env, id };
		pthread_create(&threads_arr[id], NULL, draw_threads, &data[id]);
	}
	id = UINT32_MAX;
	while (threads > ++id)
		pthread_join(threads_arr[id], NULL);
	argb_shift(env, env->param.color_shift);
	redraw_fract_or_img(env, env->param, env->flags, 1);
	free(data);
	free(threads_arr);
}
