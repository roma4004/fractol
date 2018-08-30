/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:13:08 by dromanic          #+#    #+#             */
/*   Updated: 2018/08/30 17:24:48 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	draw_fractal(t_win *win)
{
//	int		i;
//	int 	x;
//	int 	y;
	t_img	*img;

	img = win->img;
//	y = -1;
//	while(++y < WIN_HEIGHT)
//	{
//		x = -1;
//		while (++x < WIN_WIDTH)
//		{
//			i = get_fractal_point(win, x, y);
//			px_to_img(img, x, y, get_color(gen_color(win, i)));
//		}
//	}
	paralel_put_to_img(win);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, img->img_ptr, 0, 0);
}

void	*parallel_draw(void *thread_data)
{
	int		col;
	int		x;
	int		y;
	t_win	*win;
	t_pth_dt	*thread_dt;

	thread_dt = (t_pth_dt *)thread_data;
	win = thread_dt->win;
	y = (WIN_HEIGHT / 2  * -1) / win->param->zoom;
	while(y < WIN_HEIGHT)
	{
		x = (WIN_WIDTH / 2 * -1) / win->param->zoom;
		while (x < WIN_WIDTH)
		{
			col = get_fractal_col(win, x, y + thread_dt->offset);
			px_to_img(win->img, x, y + thread_dt->offset, col);
			x++;
		}
		y += win->param->cpu_cores;
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
	int			id;
	int			id_max;
	t_pth_dt	*data;
	pthread_t	*pthreads;
	
	pthreads = init_pthreads(win);
	data = (t_pth_dt *)malloc(sizeof(t_pth_dt) * win->param->cpu_cores);
	id_max = win->param->cpu_cores;
	id = -1;
	while (++id < id_max)
	{
		data[id].win = win;
		data[id].offset = id;
		pthread_create(&pthreads[id], NULL, parallel_draw, &data[id]);
	}
	id = -1;
	while (++id < id_max)
		pthread_join(pthreads[id], NULL);
}

int		main(void)//int argc, char **argv)
{
	t_win *win;

	printf("cores: %d", get_processors_num());
	win = init_win();

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

	/*

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
