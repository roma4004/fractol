/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 20:43:55 by dromanic          #+#    #+#             */
/*   Updated: 2018/12/25 19:00:32 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "main.h"

static void	px_to_img(t_img *img, t_int_pt pt, int color)
{
	if (img
		&& pt.x >= 0 && pt.x < (int)WIN_WIDTH
		&& pt.y >= 0 && pt.y < (int)WIN_HEIGHT)
		img->data[pt.y * (int)WIN_WIDTH + pt.x] = color;
}

static void	barnsley_part(t_param *param, char part, t_cnb *c)
{
	c->rold = c->r;
	c->iold = c->i;
	if (part == BARNSLEY_PART_BODY)
	{
		c->r = 0;
		c->i = 0.16f * c->iold;
	}
	else if (part == BARNSLEY_PART_RIGHT)
	{
		c->r = -0.15f * c->rold + 0.28f * c->iold;
		c->i = 0.26f * c->rold + 0.24f * c->iold + 0.44f;
	}
	else if (part == BARNSLEY_PART_LEFT)
	{
		c->r = 0.2f * c->rold + -0.26f * c->iold;
		c->i = 0.23f * c->rold + 0.22f * c->iold + 1.6f;
	}
	else
	{
		c->r = 0.85 * c->rold + param->spec1 * c->iold;
		c->i = -0.04 * c->rold + param->spec2 * c->iold + 1.6;
	}
}

int			draw_barnsley(t_env *env, t_int_pt pt)
{
	float		rng;
	long long	px_cnt;
	t_cnb		c;
	t_param *param;

	param = env->param;
	c = (t_cnb){.r = 0, .i = 0};
	px_cnt = param->depth;
	while (px_cnt--)
	{
		rng = (float)rand() / (float)RAND_MAX;
		if (rng <= 0.01f)
			barnsley_part(param, BARNSLEY_PART_BODY, &c);
		else if (rng <= 0.06f)
			barnsley_part(param, BARNSLEY_PART_RIGHT, &c);
		else if (rng <= 0.14f)
			barnsley_part(param, BARNSLEY_PART_LEFT, &c);
		else
			barnsley_part(param, BARNSLEY_PART_CURVE, &c);
		pt.x = (int)((c.r + 4) * param->actial_zoom - param->offset.x);
		pt.y = (int)(WIN_HEIGHT - c.i * param->actial_zoom - param->offset.y);
		px_to_img(env->img->ptr, pt, 0x007700);
	}
	redraw_fract_or_img(env, param, 1);
	return (0);
}

static void	*draw_threads(void *thread_data)
{
	t_int_pt	pt;
	int			offset;
	t_env		*env;
	t_param		*param;

	if (!thread_data)
		return (NULL);
	offset = ((t_pth_dt *)thread_data)->offset;
	env = ((t_pth_dt *)thread_data)->env;
	param = env->param;
	pt.y = -1;
	while (++pt.y < (int)WIN_HEIGHT)
	{
		pt.x = 0;
		while (pt.x < (int)WIN_WIDTH)
		{
			pt.x += offset;
			px_to_img(env->img, pt, env->get_px[param->fr_id](env, pt));
			//| 0xf0000000);// << | 0xf0000000 //NEW BONUS
			pt.x -= offset;
			pt.x += param->threads;
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
	redraw_fract_or_img(env, env->param, 1);
	argb_shift(env, &env->param->col_shift);
}