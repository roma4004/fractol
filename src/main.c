/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:13:08 by dromanic          #+#    #+#             */
/*   Updated: 2018/09/02 16:46:57 by dromanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	draw_fractal(t_env *win)
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
	parallel_draw_fractal(win);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, img->ptr, 0, 0);
}


int		main(void)//int argc, char **argv)
{
	t_env *win;

	win = init_win();
	//if (argc > 1 && (win = init_win()))
	//{
	//	if (parse_map(argv[1], win))
	//	{
	//init_mandelbrot(win->param);
	win->init_func[FR_MANDELBROT](win->param);
	redraw_fract(win);
	//parallel_draw_fractal(win);
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
		exit(1);
	}*/
	show_errors(win);
	return (0);
}
