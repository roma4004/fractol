/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:13:08 by dromanic          #+#    #+#             */
/*   Updated: 2018/08/22 21:25:34 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	draw_fractal(t_win *win)
{
	int		i;
	int 	x;
	int 	y;
	t_img	*img;

	img = win->img;
	y = -1;
	while(++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			i = get_fractal_point(win, x, y);
			px_to_img(img, x, y, get_color(gen_color(win, i)));
		}
	}
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, img->img_ptr, 0, 0);
}

void	*draw_threads(void *thread_data)
{
	int		i;
	int		x;
	int		y;
	t_win	*win;
	t_pth_dt	*thread_dt;

	thread_dt = (t_pth_dt *)thread_data;
	win = thread_dt->win;
	y = -1;
	while(++y < WIN_HEIGHT)
	{
		x = -1;
		while ((x += win->param->cpu_cores) < WIN_WIDTH)
		{
			i = get_fractal_point(win, x - thread_dt->id, y);
			px_to_img(win->img, x - thread_dt->id, y, get_color(gen_color(win, i)));
		}
	}
	return (NULL);
}

void	change_fract(t_win *win, int fr_new_type)
{
	win->param->fr_id = fr_new_type;
	init_fract(win->param, win->param->fr_id);
	redraw_fract(win);
}

void	paralel_put_to_img(t_win *win)
{
	int			i;
	int			id_max;
	t_pth_dt	**thread_dt;

	thread_dt = (t_pth_dt **)malloc(sizeof(t_pth_dt) * win->param->cpu_cores);
	id_max = win->param->cpu_cores;
	i = -1;
	while (++i < id_max)
	{
		thread_dt[i] = init_pthread_dt(win, i);
		pthread_create(&win->pthreads_id[i], NULL, draw_threads, thread_dt[i]);
	}
	i = -1;
	while (++i < id_max)
		pthread_join(win->pthreads_id[i], NULL);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img->img_ptr, 0, 0);
	//завершаем поток
	//pthread_exit(0);
}

int main(void)//int argc, char **argv)
{
	//y * WIN_WIDTH + x + (thr_num - thr_id)
	t_win *win;
	//t_pth_dt *thread_data;
	int i;

	i = 0;
	printf("cores: %d", get_processors_num());
	win = init_win();
	win->pthreads_id = init_pthreads(win);

	//pthread_create();
	//	pthread_create(&thread, NULL, threadFunc, thread_data);

	//if (argc > 1 && (win = init_win()))
	//{
	//	if (parse_map(argv[1], win))
	//	{
			change_fract(win, FR_MANDELBROT);
			//redraw_fract(win);
			paralel_put_to_img(win);
			mlx_hook(win->win_ptr, 17, 1L << 17, exit_x, win);
			mlx_hook(win->win_ptr, 2, 5, deal_keyboard, win);
			mlx_mouse_hook(win->win_ptr, deal_mouse, win);
			mlx_loop(win->mlx_ptr);
	//	}
	//}
	/*t_win	*win;

	if (argc == 2 && (win = init_win()))
	{
		if (parse_map(argv[1], win))
		{
			draw_map(win);
			mlx_hook(win->win_ptr, 17, 1L << 17, exit_x, win);
			mlx_hook(win->win_ptr, 2, 5, deal_keyboard, win);
			mlx_mouse_hook(win->win_ptr, deal_mouse, win);
			mlx_loop(win->mlx_ptr);
		}
		else
		{
			show_errors(win);
			exit_x(win);
		}
	}
	else
	{
		ft_putstr("Usage: ./fdf map.fdf\n");
99		exit(1);
	}*/
	show_errors(win);
	return (0);
}
