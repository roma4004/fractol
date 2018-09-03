/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 12:29:00 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/01 19:26:30 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	px_to_img(t_img *img, int x, int y, int color)
{
	if (img
		&& x >= 0 && x < WIN_WIDTH
		&& y >= 0 && y < WIN_HEIGHT)
		img->data[y * WIN_WIDTH + x] = color;
}

static void	*draw_threads(void *thread_data)
{
	int			x;
	int			y;
	t_env		*win;
	t_param		*par;
	t_pth_dt	*data;

	if (!thread_data)
		return (NULL);
	data = (t_pth_dt *)thread_data;
	win = data->win;
	par = win->param;
	y = (int)((par->center_y * -1) / par->zoom);
	while(y < WIN_HEIGHT)
	{
		x = (int)((par->center_x * -1) / par->zoom);
		while (x < WIN_WIDTH)
		{
			px_to_img(win->img, x, y + data->offset,
					  get_fractal_col(win, x, y + data->offset));
			x++;
		}
		y += par->cpu_cores;
	}
	return (NULL);
}

void	parallel_draw_fractal(t_env *win)
{
	int			id;
	int			cpu_cores;
	t_pth_dt	*data;
	pthread_t	*threads;

	if (!win)
		return ;
	cpu_cores = win->param->cpu_cores;
	//	if (!(threads = (pthread_t *)malloc(sizeof(pthread_t) * cpu_cores))
	//	|| !(data = (t_pth_dt *)malloc(sizeof(t_pth_dt) * cpu_cores)))
	//	{
	//		ft_memdel((void *)&threads);
	//		ft_memdel((void *)&data);
	//		return ;
	//	}
	//	while (id++ < win->param->cpu_cores)
	//	threads[id] = NULL;
	threads = (pthread_t *)malloc(sizeof(pthread_t) * cpu_cores);
	data = (t_pth_dt *)malloc(sizeof(t_pth_dt) * cpu_cores);
	id = -1;
	while (++id < cpu_cores)
	{
		data[id].win = win;
		data[id].offset = id;
		pthread_create(&threads[id], NULL, draw_threads, &data[id]);
	}
	id = -1;
	while (++id < cpu_cores)
		pthread_join(threads[id], NULL);
	redraw_img(win);
}
